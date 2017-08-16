/**
 * @file loop_function_repository.cpp
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
#include "fordyca/params/loop_function_repository.hpp"
#include "fordyca/params/dynamic_grid_param_parser.hpp"
#include "fordyca/params/block_param_parser.hpp"
#include "fordyca/params/logging_param_parser.hpp"
#include "fordyca/params/loop_functions_param_parser.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca, params);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
loop_function_repository::loop_function_repository(void) {
  factory().register_type<dynamic_grid_param_parser>("dynamic_grid");
  factory().register_type<block_param_parser>("block");
  factory().register_type<logging_param_parser>("logging");
  factory().register_type<loop_functions_param_parser>("loop_functions");
  parsers()["dynamic_grid"]     = factory().create("dynamic_grid");
  parsers()["blocks"]           = factory().create("block");
  parsers()["logging"]          = factory().create("logging");
  parsers()["loop_functions"]   = factory().create("loop_functions");
}

NS_END(params, fordyca);
