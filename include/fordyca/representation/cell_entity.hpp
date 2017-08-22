/**
 * @file cell_entity.hpp
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

#ifndef INCLUDE_FORDYCA_REPRESENTATION_CELL_ENTITY_HPP_
#define INCLUDE_FORDYCA_REPRESENTATION_CELL_ENTITY_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <utility>
#include <argos3/core/utility/math/vector2.h>
#include "rcppsw/common/common.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca, representation);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class cell_entity {
 public:
  typedef std::pair<size_t, size_t> discrete_coord;

  cell_entity(double x_dim, double y_dim) : m_id(-1),
                                            m_display_id(false),
                                            m_x_dim(x_dim), m_y_dim(y_dim),
                                            m_real_loc(), m_discrete_loc() {}

  double xsize(void) const { return m_x_dim; }
  double ysize(void) const { return m_y_dim; }
  void display_id(bool display_id) { m_display_id = display_id; }
  bool display_id(void) const { return m_display_id; }

  const argos::CVector2& real_loc(void) const { return m_real_loc; }
  const discrete_coord& discrete_loc(void) const { return m_discrete_loc; }
  void real_loc(const argos::CVector2& loc) { m_real_loc = loc; }
  void discrete_loc(const discrete_coord& loc) { m_discrete_loc = loc; }
  void id(int id) { m_id = id; }
  int id(void) const { return m_id; }

 private:
  int m_id;
  bool m_display_id;
  double m_x_dim;
  double m_y_dim;
  argos::CVector2 m_real_loc;
  discrete_coord m_discrete_loc;
};

NS_END(representation, fordyca);

#endif /* INCLUDE_FORDYCA_REPRESENTATION_CELL_ENTITY_HPP_ */