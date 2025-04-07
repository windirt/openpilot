# MIT Non-Commercial License
#
# Copyright (c) 2019, dragonpilot
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, for non-commercial purposes only, subject to the following conditions:
#
# - The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
# - Commercial use (e.g., use in a product, service, or activity intended to generate revenue) is prohibited without explicit written permission from dragonpilot. Contact ricklan@gmail.com for inquiries.
# - Any project that uses the Software must visibly mention the following acknowledgment: "This project uses software from dragonpilot and is licensed under a custom license requiring permission for use."
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
# Downhill Coasting allows the vehicle to maintain or slightly increase speed on downhill slopes without braking.

import numpy as np

SLOPE = -0.04
RATIO = 0.9

TTC = 5.
TTC_BP = [5.0, 3.0]
MIN_BRAKE_ALLOW_VALS = [0., -0.5]

class ACM:
  def __init__(self, enabled = False, downhill_only = False):
    self._enabled = enabled
    self._downhill_only = downhill_only
    self._is_downhill = False
    self._is_speed_over_cruise = False
    self._has_lead = False
    self._active_prev = False

    self.active = False
    self.just_disabled = False
    self.allowed_brake_val = 0.

  def update_states(self, cs, rs, user_ctrl_lon, v_ego, v_cruise):
    self.lead_ttc = float('inf')  # Default if no lead

    if not self._enabled:
      self.active = False
      return

    if len(cs.orientationNED) != 3:
      self.active = False
      return

    pitch_rad = cs.orientationNED[1]
    self._is_downhill = np.sin(pitch_rad) < SLOPE
    self._is_speed_over_cruise = v_ego > (v_cruise * RATIO)

    lead = rs.leadOne
    if lead and lead.status:
      self.lead_ttc = lead.dRel / v_ego if v_ego > 0 else float('inf')
      self.allowed_brake_val = np.interp(self.lead_ttc, TTC_BP, MIN_BRAKE_ALLOW_VALS)
      self._has_lead = self.lead_ttc < TTC
    else:
      self._has_lead = False

    self.active = not user_ctrl_lon and not self._has_lead and self._is_speed_over_cruise and (self._is_downhill if self._downhill_only else True)

    self.just_disabled = self._active_prev and not self.active
    self._active_prev = self.active

  def update_a_desired_trajectory(self, a_desired_trajectory):
    if not self.active:
      return a_desired_trajectory

    # Suppress all braking to allow smooth coasting
    for i in range(len(a_desired_trajectory)):
      if a_desired_trajectory[i] < 0 and a_desired_trajectory[i] > self.allowed_brake_val:
        a_desired_trajectory[i] = 0.0
    return a_desired_trajectory

  def update_output_a_target(self, output_a_target):
    if not self.active:
      return output_a_target

    # Suppress braking
    if output_a_target < 0 and output_a_target > self.allowed_brake_val:
      output_a_target = 0.0
    return output_a_target

  def set_enabled(self, enabled):
    self._enabled = enabled

  def set_downhill_only(self, downhill_only):
    self._downhill_only = downhill_only
