/**
 * @file free_block_drop.hpp
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

#ifndef INCLUDE_FORDYCA_EVENTS_FREE_BLOCK_DROP_HPP_
#define INCLUDE_FORDYCA_EVENTS_FREE_BLOCK_DROP_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fordyca/events/block_drop_event.hpp"
#include "fordyca/events/cell_op.hpp"
#include "rcppsw/er/client.hpp"
#include "rcppsw/math/dcoord.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca);

namespace visitor = rcppsw::patterns::visitor;

NS_START(events);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @class free_block_drop
 * @ingroup events
 *
 * @brief Created whenever a block is dropped somewhere in the arena that is not
 * a cache or the nest.
 *
 * This can happen when:
 *
 * - The loop functions are doing block distribution.
 * - A robot aborts its task, and is carrying a block.
 */
class free_block_drop : public cell_op,
                        public rcppsw::er::client,
                        public block_drop_event {
 public:
  free_block_drop(const std::shared_ptr<rcppsw::er::server>& server,
                  const std::shared_ptr<representation::block>& block,
                  size_t x,
                  size_t y,
                  double resolution);
  ~free_block_drop(void) override { client::rmmod(); }

  free_block_drop(const free_block_drop& op) = delete;
  free_block_drop& operator=(const free_block_drop& op) = delete;

  /* stateless foraging */
  void visit(representation::cell2D& cell) override;
  void visit(representation::block& block) override;
  void visit(fsm::cell2D_fsm& fsm) override;
  void visit(representation::arena_map& map) override;

  /* depth1 foraging */
  void visit(controller::depth1::foraging_controller&) override {}

  /**
   * @brief Get the handle on the block that has been dropped.
   */
  std::shared_ptr<representation::block> block(void) const { return m_block; }

 private:
  // clang-format off
  double                                 m_resolution;
  std::shared_ptr<representation::block> m_block;
  std::shared_ptr<rcppsw::er::server>    m_server;
  // clang-format on
};

NS_END(events, fordyca);

#endif /* INCLUDE_FORDYCA_EVENTS_FREE_BLOCK_DROP_HPP_ */
