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

from openpilot.common.swaglog import cloudlog
import numpy as np

SLOPE = -0.05
TTC = 2.5
RATIO = 0.95

class DHC:
  def __init__(self, enabled):
    self._enabled = enabled
    self._is_downhill = False
    self._is_speed_over_cruise = False
    self._has_lead = False

  def update_states(self, cs, rs, v_ego, v_cruise):
    if not self._enabled:
      return

    if len(cs.orientationNED) != 3:
      return

    pitch_rad = cs.orientationNED[1]
    self._is_downhill = np.sin(pitch_rad) < SLOPE
    self._is_speed_over_cruise = v_ego > (v_cruise * RATIO)
    lead_ttc = rs.leadOne.dRel / v_ego if v_ego > 0 else float('inf')
    self._has_lead = rs.leadOne.status and rs.leadOne and lead_ttc < TTC

  def set_min_accel(self, min_accel):
    if not self._enabled:
      return min_accel

    if self._is_downhill and not self._has_lead and self._is_speed_over_cruise:
      cloudlog.info("DHC Engaged")
      return max(min_accel, 0.)

    return min_accel
