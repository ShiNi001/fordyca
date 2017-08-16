/**
 * @file controller_repository.cpp
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
#include "fordyca/params/controller_repository.hpp"
#include "fordyca/params/actuator_param_parser.hpp"
#include "fordyca/params/sensor_param_parser.hpp"
#include "fordyca/params/fsm_param_parser.hpp"
#include "fordyca/params/perceived_grid_param_parser.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca, params);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
controller_repository::controller_repository(void) {
  factory().register_type<actuator_param_parser>("actuators");
  factory().register_type<sensor_param_parser> ("sensors");
  factory().register_type<fsm_param_parser>("fsm");
  factory().register_type<perceived_grid_param_parser>("perceived_grid");
  parsers()["actuators"]        = factory().create("actuators");
  parsers()["sensors"]          = factory().create("sensors");
  parsers()["fsm"]              = factory().create("fsm");
  parsers()["perceived_grid"]   = factory().create("perceived_grid");
}

NS_END(params, fordyca);
