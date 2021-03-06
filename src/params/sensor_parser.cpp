/**
 * @file sensor_parser.cpp
 *
 * @copyright 2017 John Harwell, All rights reserved.
 *
 * This file is part of FORDYCA.
 *
 * FORDYCA is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * FORDYCA is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * FORDYCA.  If not, see <http://www.gnu.org/licenses/
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fordyca/params/sensor_parser.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca, params);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void sensor_parser::parse(argos::TConfigurationNode& node) {
  argos::TConfigurationNode diff_node =
      argos::GetNode(argos::GetNode(node, "sensors"), "proximity");
  m_params = rcppsw::make_unique<struct sensor_params>();

  argos::GetNodeAttribute(diff_node,
                          "go_straight_angle_range",
                          m_params->proximity.go_straight_angle_range);
  argos::GetNodeAttribute(diff_node, "delta", m_params->proximity.delta);
} /* parse() */

void sensor_parser::show(std::ostream& stream) {
  stream << "====================\nSensor params\n====================\n";
  stream << "delta=" << m_params->proximity.delta << std::endl;
  stream << "go_straight_angle_range="
         << m_params->proximity.go_straight_angle_range << std::endl;
} /* show() */

__pure bool sensor_parser::validate(void) {
  if (!(m_params->proximity.go_straight_angle_range.GetSpan().GetAbsoluteValue() >
        0)) {
    return false;
  }
  if (m_params->proximity.delta <= 0) {
    return false;
  }
  return true;
} /* validate() */

NS_END(params, fordyca);
