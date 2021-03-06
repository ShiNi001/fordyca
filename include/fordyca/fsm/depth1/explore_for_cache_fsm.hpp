/**
 * @file explore_for_cache_fsm.hpp
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

#ifndef INCLUDE_FORDYCA_FSM_DEPTH1_EXPLORE_FOR_CACHE_FSM_HPP_
#define INCLUDE_FORDYCA_FSM_DEPTH1_EXPLORE_FOR_CACHE_FSM_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <argos3/core/utility/math/vector2.h>
#include <argos3/core/utility/math/rng.h>

#include "fordyca/fsm/base_explore_fsm.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca);

namespace controller { namespace depth1 {class foraging_sensors; }}

NS_START(fsm, depth1);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @class explore_for_cache_fsm
 * @ingroup fsm depth1
 *
 * @brief Robots executing this task will roam around randomly looking for a
 * cache. Once they have found one, the FSM will signal that its task is
 * complete.
 */
class explore_for_cache_fsm : public base_explore_fsm {
 public:
  enum fsm_states {
    ST_START,
    /**
     * Roaming around looking for a cache.
     */
    ST_EXPLORE,

    /**
     * Obstacle nearby--avoid it.
     */
    ST_COLLISION_AVOIDANCE,

    /**
     * Changing direction to a (hopefully) more profitable search trajectory.
     */
    ST_NEW_DIRECTION,

    /**
     * A cache has been acquired.
     */
    ST_FINISHED,
    ST_MAX_STATES
  };

  explore_for_cache_fsm(uint unsuccessful_dir_change_thresh,
                        const std::shared_ptr<rcppsw::er::server>& server,
                        const std::shared_ptr<controller::depth1::foraging_sensors>& sensors,
                        const std::shared_ptr<controller::actuator_manager>& actuators);

  explore_for_cache_fsm(const explore_for_cache_fsm& fsm) = delete;
  explore_for_cache_fsm& operator=(const explore_for_cache_fsm& fsm) = delete;

  /* taskable overrides */
  void task_execute(void) override;
  bool task_finished(void) const override { return ST_FINISHED == current_state(); }
  bool task_running(void) const override;
  void task_reset(void) override { init(); }

  /**
   * @brief Reset the FSM
   */
  void init(void) override;

  /**
   * @brief Get if the robot is currently engaged in collision avoidance.
   *
   * @return \c TRUE if the condition is met, \c FALSE otherwise.
   */
  bool is_avoiding_collision(void) const {
    return current_state() == ST_COLLISION_AVOIDANCE;
  }

 private:
  /* inherited states */
  HFSM_STATE_INHERIT_ND(base_foraging_fsm, collision_avoidance);
  HFSM_STATE_INHERIT(base_foraging_fsm, new_direction, state_machine::event_data);
  HFSM_ENTRY_INHERIT_ND(base_foraging_fsm, entry_collision_avoidance);
  HFSM_ENTRY_INHERIT_ND(base_foraging_fsm, entry_new_direction);
  HFSM_ENTRY_INHERIT_ND(base_explore_fsm, entry_explore);

  /* exploration states */

  /**
   * @brief Starting/reset state for FSM. Has no purpose other than that.
   */
  HFSM_STATE_DECLARE_ND(explore_for_cache_fsm, start);

  /**
   * @brief The main state for the explore FSM. Robots in this state maintain
   * their heading, looking for a cache, until they find it or exceed the
   * direction change threshold.
   */
  HFSM_STATE_DECLARE_ND(explore_for_cache_fsm, explore);
  HFSM_STATE_DECLARE_ND(explore_for_cache_fsm, finished);

  /**
   * @brief Defines the state map for the FSM.
   *
   * Note that the order of the states in the map MUST match the order of the
   * states in \enum fsm_states, or things will not work correctly.
   */
  HFSM_DEFINE_STATE_MAP_ACCESSOR(state_map_ex, index) override {
    return &mc_state_map[index];
  }

  std::shared_ptr<controller::depth1::foraging_sensors> m_sensors;
  HFSM_DECLARE_STATE_MAP(state_map_ex, mc_state_map, ST_MAX_STATES);
};

NS_END(depth1, fsm, fordyca);

#endif /* INCLUDE_FORDYCA_FSM_DEPTH1_EXPLORE_FOR_CACHE_FSM_HPP_ */
