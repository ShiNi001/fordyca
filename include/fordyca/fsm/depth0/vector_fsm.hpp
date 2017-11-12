/**
 * @file vector_fsm.hpp
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

#ifndef INCLUDE_FORDYCA_FSM_DEPTH0_VECTOR_FSM_HPP_
#define INCLUDE_FORDYCA_FSM_DEPTH0_VECTOR_FSM_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <argos3/core/utility/math/vector2.h>
#include <argos3/core/utility/math/rng.h>
#include "rcppsw/task_allocation/polled_simple_fsm.hpp"
#include "rcppsw/control/pid_loop.hpp"
#include "fordyca/tasks/argument.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca);

namespace controller {
namespace depth0 { class foraging_sensors; }
class actuator_manager;
} /* namespace controller */

namespace state_machine = rcppsw::patterns::state_machine;
NS_START(fsm, depth0);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class vector_fsm : public rcppsw::task_allocation::polled_simple_fsm {
 public:
  vector_fsm(uint frequent_collision_thresh,
             std::shared_ptr<rcppsw::common::er_server> server,
             std::shared_ptr<controller::depth0::foraging_sensors> sensors,
             std::shared_ptr<controller::actuator_manager> actuators);

  /* taskable overrides */

  /**
   * @brief Reset the vector-to-goal task to a state where it can be restarted.
  */
  void task_reset(void) override { init(); }

  /**
   * @brief Determine if the robot is still on the way to the specified
   * goal. Basically a way of checking if a robot is still in transit.
   *
   * @return TRUE if the condition is met, FALSE otherwise.
   */
  bool task_running(void) const override {
    return current_state() != ST_START && current_state() != ST_ARRIVED;
  }

  /**
   * @brief (Re)start the FSM, with a new goal.
   *
   * @param arg The (X, Y) coordinates of the new goal to drive to.
   */
  void task_start(const rcppsw::task_allocation::taskable_argument* const arg) override;

  /**
   * @brief Determine if the robot has arrived at the specified goal within the
   * specified tolerance yet.
   *
   * @return TRUE if the condition is met, FALSE otherwise.
   */
  bool task_finished(void) const override { return current_state() == ST_ARRIVED; }


  /**
   * @brief Initialize/re-initialize the vector_fsm fsm. After arriving at a
   * goal, this function must be called before vectoring to a new goal will work.
   */
  void init(void) override;


  bool is_avoiding_collision(void) const {
    return ST_COLLISION_AVOIDANCE == current_state() ||
        ST_COLLISION_AVOIDANCE == current_state();
  }

 protected:
  enum fsm_states {
    ST_START,
    ST_VECTOR,
    ST_COLLISION_AVOIDANCE,
    ST_COLLISION_RECOVERY,
    ST_ARRIVED,
    ST_MAX_STATES
  };

 private:
  /* types */

  /**
   * @brief A structure containing all the information needed for the controller
   * to tell the FSM where to travel to next.
   */
  struct goal_data : public rcppsw::patterns::state_machine::event_data {
    explicit goal_data(argos::CVector2 goal_) : goal(goal_) {}
    goal_data(void) : goal() {}

    argos::CVector2 goal;
  };

  struct fsm_state {
    fsm_state(void) : last_collision_time(0) {}
    uint last_collision_time;
  };

  /* constants */

  /**
   * @brief The # of timesteps according to collision recovery. This is mainly
   * to ensure that you do not repeatedly get 2 robots butting heads as they try
   * to travel to opposite goals.
   */
  static uint kCOLLISION_RECOVERY_TIME;

  /**
   * @brief The tolerance within which a robot's location has to be in order to
   * be considered having arrived at a specified target location.
   */
  static double kVECTOR_FSM_MIN_DIFF;

  /* member functions */
  argos::CVector2 randomize_vector_angle(argos::CVector2 v);

  /**
   * @brief Calculates the relative vector from the robot to the current goal.
   *
   * @param goal The current goal.
   *
   * @return The vector, specified with the tail at the robot and the head
   * pointing towards the goal.
   */
  argos::CVector2 calc_vector_to_goal(const argos::CVector2& goal);

  /* states */
  FSM_STATE_DECLARE_ND(vector_fsm, start);
  FSM_STATE_DECLARE(vector_fsm, vector, struct goal_data);
  FSM_STATE_DECLARE_ND(vector_fsm, collision_avoidance);
  FSM_STATE_DECLARE_ND(vector_fsm, collision_recovery);
  FSM_STATE_DECLARE(vector_fsm, arrived, struct goal_data);

  FSM_ENTRY_DECLARE_ND(vector_fsm, entry_vector);
  FSM_ENTRY_DECLARE_ND(vector_fsm, entry_collision_avoidance);
  FSM_ENTRY_DECLARE_ND(vector_fsm, entry_collision_recovery);

  FSM_DEFINE_STATE_MAP_ACCESSOR(state_map_ex, index) override {
    FSM_DEFINE_STATE_MAP(state_map_ex, kSTATE_MAP) {
      FSM_STATE_MAP_ENTRY_EX_ALL(&start, NULL, NULL, NULL),
          FSM_STATE_MAP_ENTRY_EX_ALL(&vector, NULL, &entry_vector, NULL),
          FSM_STATE_MAP_ENTRY_EX_ALL(&collision_avoidance, NULL,
                                     &entry_collision_avoidance, NULL),
          FSM_STATE_MAP_ENTRY_EX_ALL(&collision_recovery, NULL,
                                     &entry_collision_recovery, NULL),
          FSM_STATE_MAP_ENTRY_EX_ALL(&arrived, NULL, NULL, NULL)
          };
    return &kSTATE_MAP[index];
  }

  vector_fsm(const vector_fsm& fsm) = delete;
  vector_fsm& operator=(const vector_fsm& fsm) = delete;

  /* data members */

  argos::CRandom::CRNG* m_rng;
  struct fsm_state m_state;
  uint m_freq_collision_thresh;
  uint m_collision_rec_count;
  std::shared_ptr<controller::depth0::foraging_sensors> m_sensors;
  std::shared_ptr<controller::actuator_manager> m_actuators;
  argos::CVector2 m_goal;
  rcppsw::control::pid_loop m_ang_pid;
  rcppsw::control::pid_loop m_lin_pid;
};

NS_END(depth0, fsm, fordyca);

#endif /* INCLUDE_FORDYCA_FSM_DEPTH0_VECTOR_FSM_HPP_ */