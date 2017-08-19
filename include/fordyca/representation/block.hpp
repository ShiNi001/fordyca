/**
 * @file block.hpp
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

#ifndef INCLUDE_FORDYCA_REPRESENTATION_BLOCK_HPP_
#define INCLUDE_FORDYCA_REPRESENTATION_BLOCK_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fordyca/representation/cell_entity.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca, representation);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A representation of a block within the arena map. Blocks do not have
 * state (other than if they are currently being carried by a robot). Blocks
 * have both real (where they actually live in the world) and discretized
 * locations (where they are mapped to within the arena map).
 */
class block : public cell_entity {
 public:
  explicit block(double dimension) :
      cell_entity(dimension, dimension),
      m_robot_index(-1), m_carries(0) {}

  size_t carries(void) const { return m_carries; }
  bool contains_point(const argos::CVector2& point);
  int robot_index(void) const { return m_robot_index; }

  /* events */
  void event_pickup(size_t index);
  void event_nest_drop(void) { m_carries = 0; m_robot_index = -1; }

 private:
  int m_robot_index;
  size_t m_carries;
};

NS_END(representation, fordyca);

#endif /* INCLUDE_FORDYCA_REPRSENTATION_BLOCK_HPP_ */
