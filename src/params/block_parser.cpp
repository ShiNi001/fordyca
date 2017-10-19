/**
 * @file block_parser.cpp
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
#include "fordyca/params/block_parser.hpp"
#include "rcppsw/utils/line_parser.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca, params);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void block_parser::parse(argos::TConfigurationNode& node) {
  m_params.reset(new struct block_params);

  argos::TConfigurationNode bnode = argos::GetNode(node, "blocks");
  argos::GetNodeAttribute(bnode, "n_blocks", m_params->n_blocks);
  argos::GetNodeAttribute(bnode, "dimension", m_params->dimension);
  argos::GetNodeAttribute(bnode, "dist_model", m_params->dist_model);
  argos::GetNodeAttribute(bnode, "respawn", m_params->respawn);
} /* parse() */

void block_parser::show(std::ostream& stream) {
  stream << "====================\nBlock params\n====================\n";
  stream << "n_blocks=" << m_params->n_blocks << std::endl;
  stream << "dimension=" << m_params->dimension << std::endl;
  stream << "dist_model=" << m_params->dist_model << std::endl;
  stream << "respawn=" << m_params->respawn << std::endl;
} /* show() */

NS_END(params, fordyca);
