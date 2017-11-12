/**
 * @file block_target_selector.hpp
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

#ifndef INCLUDE_FORDYCA_CONTROLLER_DEPTH0_BLOCK_SELECTOR_HPP_
#define INCLUDE_FORDYCA_CONTROLLER_DEPTH0_BLOCK_SELECTOR_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <list>
#include <utility>

#include "rcppsw/common/er_client.hpp"
#include "fordyca/representation/block.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca, controller, depth0);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class block_selector: public rcppsw::common::er_client {
 public:
  block_selector(
      const std::shared_ptr<rcppsw::common::er_server>& server,
      argos::CVector2 nest_loc);

  ~block_selector(void) { rmmod(); }

  /**
   * @brief Given a list of blocks that a robot knows about (i.e. have not faded
   * into an unknown state), compute which is the "best", for use in deciding
   * which block to go attempt to pickup.
   *
   * @return A pointer to the "best" block, along with its utility value.
   */
  representation::perceived_block calc_best(
      const std::list<representation::perceived_block> blocks,
      argos::CVector2 robot_loc);

 private:
  argos::CVector2 m_nest_loc;
};

NS_END(depth0, fordyca, controller);

#endif /* INCLUDE_FORDYCA_CONTROLLER_DEPTH0_BLOCK_SELECTOR_HPP_ */