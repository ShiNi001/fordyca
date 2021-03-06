/**
 * @file arena_map_parser.cpp
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
#include "fordyca/params/arena_map_parser.hpp"
#include "rcppsw/utils/line_parser.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca, params);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void arena_map_parser::parse(argos::TConfigurationNode& node) {
  m_params = rcppsw::make_unique<struct arena_map_params>();
  argos::TConfigurationNode anode = argos::GetNode(node, "arena_map");

  m_grid_parser.parse(argos::GetNode(anode, "grid"));
  m_params->grid = *m_grid_parser.get_results();

  m_block_parser.parse(argos::GetNode(anode, "blocks"));
  m_params->block = *m_block_parser.get_results();

  m_cache_parser.parse(argos::GetNode(anode, "caches"));
  m_params->cache = *m_cache_parser.get_results();

  std::vector<std::string> res, res2;
  rcppsw::utils::line_parser parser(' ');

  res = parser.parse(argos::GetNode(anode, "nest").GetAttribute("center"));
  res2 = parser.parse(argos::GetNode(anode, "nest").GetAttribute("size"));

  m_params->nest_center =
      argos::CVector2(std::atof(res[0].c_str()), std::atof(res[1].c_str()));
  m_params->nest_x.Set(std::atof(res[0].c_str()) - std::atof(res2[0].c_str()),
                       std::atof(res[0].c_str()) + std::atof(res2[0].c_str()));
  m_params->nest_y.Set(std::atof(res[1].c_str()) - std::atof(res2[1].c_str()),
                       std::atof(res[1].c_str()) + std::atof(res2[1].c_str()));
} /* parse() */

void arena_map_parser::show(std::ostream& stream) {
  stream << "====================\nArena_Map params\n====================\n";
  m_grid_parser.show(stream);
  m_block_parser.show(stream);
  m_cache_parser.show(stream);
  stream << "nest_x=" << m_params->nest_x << std::endl;
  stream << "nest_y=" << m_params->nest_y << std::endl;
  stream << "nest_center=" << m_params->nest_center << std::endl;
} /* show() */

bool arena_map_parser::validate(void) {
  if (!m_grid_parser.validate() || !m_block_parser.validate() ||
      !m_cache_parser.validate()) {
    return false;
  }
  if (!(m_params->nest_center.GetX() > 0) ||
      !(m_params->nest_center.GetY() > 0)) {
    return false;
  }
  if (!(m_params->nest_x.GetMin() > 0) || !(m_params->nest_x.GetMax() > 0)) {
    return false;
  }
  if (!(m_params->nest_y.GetMin() > 0) || !(m_params->nest_y.GetMax() > 0)) {
    return false;
  }
  return true;
} /* validate() */

NS_END(params, fordyca);
