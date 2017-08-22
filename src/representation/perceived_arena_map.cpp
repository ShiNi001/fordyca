/**
 * @file perceived_arena_map.cpp
 *
 * @copyright 2017 John Harwell, All rights reserved.
 *
 * This file is part of RCPPSW.
 *
 * RCPPSW is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * RCPPSW is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * RCPPSW.  If not, see <http://www.gnu.org/licenses/
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fordyca/representation/perceived_arena_map.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca, representation);

/*******************************************************************************
 * Events
 ******************************************************************************/
void perceived_arena_map::event_block_pickup(block* block) {
  perceived_cell2D& cell = m_grid.access(block->discrete_loc().first,
                                         block->discrete_loc().second);
  cell.event_encounter(cell2D_fsm::ST_EMPTY);
} /* event_block_pickup() */

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
std::list<const block*> perceived_arena_map::blocks(void) {
  std::list<const block*> blocks;
  for (size_t i = 0; i < m_grid.xsize(); ++i) {
    for (size_t j = 0; j < m_grid.ysize(); ++j) {
      if (m_grid.access(i, j).state_has_block()) {
        blocks.push_back(m_grid.access(i, j).block());
      }
    } /* for(j..) */
  } /* for(i..) */
  return blocks;
} /* blocks() */

void perceived_arena_map::update_relevance(void) {
  for (size_t i = 0; i < m_grid.xsize(); ++i) {
    for (size_t j = 0; j < m_grid.ysize(); ++j) {
      m_grid.access(i, j).update_relevance();
    } /* for(j..) */
  } /* for(i..) */
} /* update_relevance() */


NS_END(representation, fordyca);