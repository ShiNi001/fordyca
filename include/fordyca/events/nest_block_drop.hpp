/**
 * @file nest_block_drop.hpp
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

#ifndef INCLUDE_FORDYCA_EVENTS_NEST_BLOCK_DROP_HPP_
#define INCLUDE_FORDYCA_EVENTS_NEST_BLOCK_DROP_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "rcppsw/patterns/visitor/visitor.hpp"
#include "rcppsw/er/client.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca);

namespace visitor = rcppsw::patterns::visitor;

namespace fsm {
namespace depth0 { class stateless_foraging_fsm; class stateful_foraging_fsm; }
namespace depth1 { class block_to_cache_fsm; }
class block_to_nest_fsm;
}
namespace controller {
namespace depth0 {
class stateless_foraging_controller;
class stateful_foraging_controller;
}
namespace depth1 { class foraging_controller; }
}

namespace representation { class block; class arena_map; };
namespace metrics { namespace collectors { class block_metrics_collector; }}
namespace tasks { class generalist; class collector; }

NS_START(events);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @class nest_block_drop
 *
 * @brief Fired whenever a robot drops a block in the nest. Processed by both
 * \ref arena_map and the robots, as they each need to react to it in different
 * ways.
 */
class nest_block_drop : public visitor::visitor,
                        public rcppsw::er::client,
                        public visitor::visit_set<controller::depth0::stateful_foraging_controller,
                                                  controller::depth0::stateless_foraging_controller,
                                                  controller::depth1::foraging_controller,
                                                  fsm::depth0::stateless_foraging_fsm,
                                                  fsm::depth0::stateful_foraging_fsm,
                                                  fsm::block_to_nest_fsm,
                                                  representation::block,
                                                  representation::arena_map,
                                                  tasks::generalist,
                                                  tasks::collector,
                                                  metrics::collectors::block_metrics_collector> {
 public:
  nest_block_drop(const std::shared_ptr<rcppsw::er::server>& server,
             representation::block* block);
  ~nest_block_drop(void) { client::rmmod(); }

  /* foraging support */
  /**
   * @brief Update the arena_map on a block drop by distributing the block in a
   * new location and updating the block so that it no longer thinks it is
   * carried by a robot.
   *
   * @param map The map to update
   */
  void visit(representation::arena_map& map) override;
  void visit(metrics::collectors::block_metrics_collector& collector) override;

  /* stateless foraging */
  /**
   * @brief Update a block with the knowledge that it has been dropped.
   *
   * @param block The block to update.
   */
  void visit(representation::block& block) override;
  void visit(fsm::depth0::stateless_foraging_fsm& fsm) override;

  /**
   * @brief Drop a carried block in the nest, updating state as appropriate.
   *
   * This needs to be here, rather than in the FSM, because dropping of blocks
   * needs to be done in the loop functions so the area can correctly be drawn
   * each timestep.
   */
  void visit(controller::depth0::stateless_foraging_controller& controller) override;

  /* stateful foraging */
  void visit(controller::depth0::stateful_foraging_controller& controller) override;
  void visit(fsm::depth0::stateful_foraging_fsm& fsm) override;

  /* depth1 foraging */
  void visit(controller::depth1::foraging_controller& controller) override;
  void visit(fsm::block_to_nest_fsm& fsm) override;
  void visit(tasks::collector& task) override;
  void visit(tasks::generalist& task) override;

  /**
   * @brief Get the handle on the block that has been dropped.
   */
  representation::block* block(void) const { return m_block; }

 private:
  nest_block_drop(const nest_block_drop& op) = delete;
  nest_block_drop& operator=(const nest_block_drop& op) = delete;
  representation::block* m_block;
};

NS_END(events, fordyca);

#endif /* INCLUDE_FORDYCA_EVENTS_NEST_BLOCK_DROP_HPP_ */
