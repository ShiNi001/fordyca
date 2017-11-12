/**
 * @file diagnostics_parser.cpp
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
#include "fordyca/params/diagnostics_parser.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca, params);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void diagnostics_parser::parse(argos::TConfigurationNode& node) {
  m_params.reset(new struct diagnostics_params);
  argos::TConfigurationNode lnode = argos::GetNode(node, "diagnostics");
  argos::GetNodeAttribute(lnode, "random_fname", m_params->random_fname);
  argos::GetNodeAttribute(lnode, "depth0_fname", m_params->depth0_fname);
  argos::GetNodeAttribute(lnode, "depth1_fname", m_params->depth1_fname);
  argos::GetNodeAttribute(lnode, "block_fname", m_params->block_fname);
} /* parse() */

void diagnostics_parser::show(std::ostream& stream) {
  stream << "====================\nDiagnostics params\n====================\n";
  stream << "random_fname=" << m_params->random_fname << std::endl;
  stream << "depth0_fname=" << m_params->depth0_fname << std::endl;
  stream << "depth1_fname=" << m_params->depth1_fname << std::endl;
  stream << "block_fname=" << m_params->block_fname << std::endl;
} /* show() */

NS_END(params, fordyca);