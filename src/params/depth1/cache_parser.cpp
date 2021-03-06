/**
 * @file cache_parser.cpp
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
#include "fordyca/params/depth1/cache_parser.hpp"
#include "rcppsw/utils/line_parser.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca, params, depth1);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void cache_parser::parse(argos::TConfigurationNode& node) {
  m_params = rcppsw::make_unique<struct cache_params>();

  argos::GetNodeAttribute(node, "dimension", m_params->dimension);
  argos::GetNodeAttribute(node, "min_dist", m_params->min_dist);
  argos::GetNodeAttribute(node, "static_size", m_params->static_size);
  argos::GetNodeAttribute(node, "usage_penalty", m_params->usage_penalty);
  argos::GetNodeAttribute(node, "create_static", m_params->create_static);
  argos::GetNodeAttribute(node, "create_dynamic", m_params->create_dynamic);
  argos::GetNodeAttribute(node,
                          "static_respawn_scale_factor",
                          m_params->static_respawn_scale_factor);
} /* parse() */

void cache_parser::show(std::ostream& stream) {
  stream << "====================\nCache params\n====================\n";
  stream << "dimension=" << m_params->dimension << std::endl;
  stream << "min_dist=" << m_params->min_dist << std::endl;
  stream << "static_size=" << m_params->static_size << std::endl;
  stream << "usage_penalty=" << m_params->usage_penalty << std::endl;
  stream << "create_static=" << m_params->create_static << std::endl;
  stream << "create_dynamic=" << m_params->create_dynamic << std::endl;
  stream << "static_respawn_scale_factor="
         << m_params->static_respawn_scale_factor << std::endl;
} /* show() */

__pure bool cache_parser::validate(void) {
  if (m_params->dimension <= 0.0) {
    return false;
  }
  if (m_params->create_static && 0 == m_params->static_size) {
    return false;
  }
  if (m_params->static_respawn_scale_factor <= 0.0) {
    return false;
  }
  return true;
} /* validate() */

NS_END(depth1, params, fordyca);
