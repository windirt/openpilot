# The MIT License
#
# Copyright (c) 2019-, Rick Lan, dragonpilot community, and a number of other of contributors.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
# Version = 2025-1-18

import numpy as np
from typing import Optional, List, Dict, Any, Union, Literal

from cereal import messaging
from opendbc.car import structs
from numpy import interp
from openpilot.common.params import Params
from openpilot.common.realtime import DT_MDL
from openpilot.sunnypilot.selfdrive.controls.lib.dec.constants import WMACConstants, SNG_State

# d-e2e, from modeldata.h
TRAJECTORY_SIZE = 33

# Speed constants
HIGHWAY_CRUISE_KPH = 70
V_ACC_MIN = 9.72

# Timing constants
STOP_AND_GO_FRAME = 60
SET_MODE_TIMEOUT = 10

# Controller modes
ControlMode = Literal['acc', 'blended']


class GenericMovingAverageCalculator:
  def __init__(self, window_size: int):
    self.window_size = window_size
    self.data: List[float] = []
    self.total: float = 0.0

  def add_data(self, value: float) -> None:
    if len(self.data) == self.window_size:
      self.total -= self.data.pop(0)
    self.data.append(value)
    self.total += value

  def get_moving_average(self) -> Optional[float]:
    return None if not self.data else self.total / len(self.data)

  def reset_data(self) -> None:
    self.data = []
    self.total = 0.0


class WeightedMovingAverageCalculator:
  def __init__(self, window_size: int):
    self.window_size = window_size
    self.data: List[float] = []
    # Linear weights increasing from 1 to 3
    self.weights = np.linspace(1, 3, window_size)

  def add_data(self, value: float) -> None:
    if len(self.data) == self.window_size:
      self.data.pop(0)
    self.data.append(value)

  def get_weighted_average(self) -> Optional[float]:
    if not self.data:
      return None

    # Use only the weights corresponding to available data
    relevant_weights = self.weights[-len(self.data):]
    weighted_sum: float = float(np.dot(self.data, relevant_weights))
    weight_total: float = float(np.sum(relevant_weights))
    return weighted_sum / weight_total

  def reset_data(self) -> None:
    self.data = []


class DynamicExperimentalController:
  def __init__(self, CP: structs.CarParams, mpc: Any, params: Optional[Params] = None):
    self._CP = CP
    self._mpc = mpc
    self._params = params or Params()
    self._enabled: bool = self._params.get_bool("DynamicExperimentalControl")
    self._active: bool = False
    self._mode: ControlMode = 'acc'
    self._frame: int = 0
    self._set_mode_timeout: int = 0

    # Initialize detectors
    self._init_detectors()

    # State variables
    self._v_ego_kph: float = 0.0
    self._v_cruise_kph: float = 0.0
    self._has_lead: bool = False
    self._has_standstill: bool = False
    self._has_standstill_prev: bool = False
    self._sng_transit_frame: int = 0
    self._sng_state: SNG_State = SNG_State.off
    self._mpc_fcw_crash_cnt: int = 0

  def _init_detectors(self) -> None:
    # Lead vehicle detector
    self._lead_gmac = WeightedMovingAverageCalculator(window_size=WMACConstants.LEAD_WINDOW_SIZE)
    self._has_lead_filtered: bool = False
    self._has_lead_filtered_prev: bool = False

    # Slow down detector
    self._slow_down_gmac = WeightedMovingAverageCalculator(window_size=WMACConstants.SLOW_DOWN_WINDOW_SIZE)
    self._has_slow_down: bool = False
    self._slow_down_confidence: float = 0.0

    # Blinker state
    self._has_blinkers: bool = False

    # Slowness detector
    self._slowness_gmac = WeightedMovingAverageCalculator(window_size=WMACConstants.SLOWNESS_WINDOW_SIZE)
    self._has_slowness: bool = False

    # Navigation instruction detector
    self._has_nav_instruction: bool = False

    # Forward collision warning detector
    self._mpc_fcw_gmac = WeightedMovingAverageCalculator(window_size=WMACConstants.MPC_FCW_WINDOW_SIZE)
    self._has_mpc_fcw: bool = False

  def _read_params(self) -> None:
    if self._frame % int(1. / DT_MDL) == 0:
      self._enabled = self._params.get_bool("DynamicExperimentalControl")

  def mode(self) -> ControlMode:
    return self._mode

  def enabled(self) -> bool:
    return self._enabled

  def active(self) -> bool:
    return self._active

  @staticmethod
  def _anomaly_detection(recent_data: List[float], threshold: float = 2.0, context_check: bool = True) -> bool:
    """
    Basic anomaly detection using standard deviation.

    Args:
        recent_data: List of recent values
        threshold: Number of standard deviations to consider anomalous
        context_check: If True, require multiple anomalies

    Returns:
        True if an anomaly is detected
    """
    if len(recent_data) < 5:
      return False

    recent_array = np.array(recent_data)
    mean: float = float(np.mean(recent_array))
    std_dev: float = float(np.std(recent_array))

    # Avoid division by zero
    if std_dev < 1e-6:
      return False

    anomaly_threshold = mean + threshold * std_dev

    # Check if the latest value is anomalous
    latest_anomaly = recent_data[-1] > anomaly_threshold

    # If context check required, verify multiple anomalies exist
    if context_check:
      return np.count_nonzero(recent_array > anomaly_threshold) > 1
    return latest_anomaly

  def _adaptive_slowdown_threshold(self) -> float:
    """
    Calculate an adaptive threshold for slow-down detection
    based on vehicle speed and recent behavior.

    Returns:
        Adaptive threshold value
    """
    # Scale threshold based on data history length (more data = higher confidence)
    slowdown_scaling_factor: float = 1.0 + 0.03 * np.log(1 + len(self._slow_down_gmac.data))

    # Interpolate base threshold from speed
    base_threshold = interp(self._v_ego_kph,
                            WMACConstants.SLOW_DOWN_BP,
                            WMACConstants.SLOW_DOWN_DIST)

    # Apply scaling factor
    return float(base_threshold * slowdown_scaling_factor)

  def _smoothed_lead_detection(self, lead_prob: float, smoothing_factor: float = 0.2) -> bool:
    """
    Apply exponential smoothing to lead detection probability.

    Args:
        lead_prob: Current lead detection probability
        smoothing_factor: Weight for new value (0-1)

    Returns:
        True if smoothed probability exceeds threshold
    """
    lead_filtering: float = (1 - smoothing_factor) * float(self._has_lead_filtered) + smoothing_factor * lead_prob
    return lead_filtering > WMACConstants.LEAD_PROB

  def _update_calculations(self, sm: messaging.SubMaster) -> None:
    car_state = sm['carState']
    lead_one = sm['radarState'].leadOne
    md = sm['modelV2']

    # Update basic state variables
    self._v_ego_kph = car_state.vEgo * 3.6
    self._v_cruise_kph = car_state.vCruise
    self._has_lead = lead_one.status
    self._has_standstill = car_state.standstill
    self._has_blinkers = car_state.leftBlinker or car_state.rightBlinker

    # Update FCW detection
    self._update_fcw_detection()

    # Update lead detection
    self._update_lead_detection(lead_one)

    # Update slow down detection
    self._update_slow_down_detection(md)

    # Update stop-and-go detection
    self._update_sng_detection()

    # Update slowness detection
    self._update_slowness_detection()

    # Keep previous values for next iteration
    self._has_standstill_prev = self._has_standstill
    self._has_lead_filtered_prev = self._has_lead_filtered

  def _update_fcw_detection(self) -> None:
    """Update forward collision warning detection."""
    self._mpc_fcw_gmac.add_data(self._mpc_fcw_crash_cnt > 0)
    if _mpc_fcw_weighted_average := self._mpc_fcw_gmac.get_weighted_average():
      self._has_mpc_fcw = _mpc_fcw_weighted_average > WMACConstants.MPC_FCW_PROB
    else:
      self._has_mpc_fcw = False

  def _update_lead_detection(self, lead_one: Any) -> None:
    self._lead_gmac.add_data(lead_one.status)
    weighted_avg = self._lead_gmac.get_weighted_average()
    if weighted_avg is not None:
      self._has_lead_filtered = weighted_avg > WMACConstants.LEAD_PROB
    else:
      self._has_lead_filtered = False

  def _update_slow_down_detection(self, md: Any) -> None:
    # Check if we have valid trajectory data
    has_valid_trajectory = (len(md.orientation.x) == len(md.position.x) == TRAJECTORY_SIZE)

    # Get adaptive threshold based on current conditions
    adaptive_threshold = self._adaptive_slowdown_threshold()

    # Determine if trajectory indicates slowdown needed
    slow_down_trigger = has_valid_trajectory and md.position.x[TRAJECTORY_SIZE - 1] < adaptive_threshold

    # Add to weighted average calculator
    self._slow_down_gmac.add_data(slow_down_trigger)

    # Get weighted average and determine if slow down is needed
    weighted_avg = self._slow_down_gmac.get_weighted_average()
    if weighted_avg is not None:
      self._has_slow_down = weighted_avg > WMACConstants.SLOW_DOWN_PROB
      self._slow_down_confidence = weighted_avg
    else:
      self._has_slow_down = False
      self._slow_down_confidence = 0.0

    # Apply anomaly detection to reduce false positives
    if self._anomaly_detection(self._slow_down_gmac.data):
      self._slow_down_confidence *= 0.85  # Reduce confidence
      self._has_slow_down = self._slow_down_confidence > WMACConstants.SLOW_DOWN_PROB

  def _update_sng_detection(self) -> None:
    if self._has_standstill:
      self._sng_state = SNG_State.stopped
      self._sng_transit_frame = 0
    else:
      if self._sng_transit_frame == 0:
        if self._sng_state == SNG_State.stopped:
          self._sng_state = SNG_State.going
          self._sng_transit_frame = STOP_AND_GO_FRAME
        elif self._sng_state == SNG_State.going:
          self._sng_state = SNG_State.off
      elif self._sng_transit_frame > 0:
        self._sng_transit_frame -= 1

  def _update_slowness_detection(self) -> None:
    if not self._has_standstill:
      # Check if current speed is significantly below cruise speed
      is_slow = self._v_ego_kph <= (self._v_cruise_kph * WMACConstants.SLOWNESS_CRUISE_OFFSET)
      self._slowness_gmac.add_data(is_slow)

      weighted_avg = self._slowness_gmac.get_weighted_average()
      if weighted_avg is not None:
        self._has_slowness = weighted_avg > WMACConstants.SLOWNESS_PROB
      else:
        self._has_slowness = False

  def _determine_control_mode(self) -> None:
    if self._CP.radarUnavailable:
      self._determine_radarless_mode()
    else:
      self._determine_radar_mode()

  def _determine_radarless_mode(self) -> None:
    # High priority conditions first
    if self._has_mpc_fcw or self._has_standstill or self._has_slow_down:
      self._set_mode('blended')
      return

    # Default back to ACC
    self._set_mode('acc')

  def _determine_radar_mode(self) -> None:
    # Forward collision warning - highest priority
    if self._has_mpc_fcw:
      self._set_mode('blended')
      return

    # Filtered lead detected and not at standstill - use ACC for smoother following
    if self._has_lead_filtered and not self._has_standstill:
      self._set_mode('acc')
      return

    # At standstill - use blended for better control
    if self._has_standstill:
      self._set_mode('blended')
      return

    # Slow down scenario detected - use blended for more control
    if self._has_slow_down:
      self._set_mode('blended')
      return

    # Below cruise speed - use ACC for comfort
    if self._has_slowness:
      self._set_mode('acc')
      return

    # Default to ACC as fallback
    self._set_mode('acc')

  def _set_mode(self, mode: ControlMode) -> None:
    if self._set_mode_timeout == 0:
      self._mode = mode
      if mode == 'blended':
        self._set_mode_timeout = SET_MODE_TIMEOUT

    if self._set_mode_timeout > 0:
      self._set_mode_timeout -= 1

  def update(self, sm: messaging.SubMaster) -> None:
    self._read_params()

    self._update_calculations(sm)

    # Determine control mode
    self._determine_control_mode()

    self._active = sm['selfdriveState'].experimentalMode and self._enabled

    self._frame += 1