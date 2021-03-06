/**
 * @file base_foraging_fsm.hpp
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

#ifndef INCLUDE_FORDYCA_FSM_BASE_FORAGING_FSM_HPP_
#define INCLUDE_FORDYCA_FSM_BASE_FORAGING_FSM_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <argos3/core/utility/math/rng.h>
#include <argos3/core/utility/math/vector2.h>
#include "fordyca/controller/kinematics_calculator.hpp"
#include "fordyca/fsm/new_direction_data.hpp"
#include "rcppsw/patterns/state_machine/hfsm.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca);

namespace controller {
class base_foraging_sensors;
class actuator_manager;
} // namespace controller
namespace state_machine = rcppsw::patterns::state_machine;
NS_START(fsm);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @class base_foraging_fsm
 * @ingroup fsm
 *
 * @brief A collection of base states/common functionality that foraging FSMs
 * can use if they choose.
 *
 * This class cannot be instantiated on its own, as does not define an FSM
 * per-se.
 */
class base_foraging_fsm : public state_machine::hfsm {
 public:
  base_foraging_fsm(uint unsuccessful_dir_change_thresh,
                    const std::shared_ptr<rcppsw::er::server>& server,
                    std::shared_ptr<controller::base_foraging_sensors> sensors,
                    std::shared_ptr<controller::actuator_manager> actuators,
                    uint8_t max_states);

  base_foraging_fsm(
      const std::shared_ptr<rcppsw::er::server>& server,
      const std::shared_ptr<controller::base_foraging_sensors>& sensors,
      const std::shared_ptr<controller::actuator_manager>& actuators,
      uint8_t max_states);

  ~base_foraging_fsm(void) override = default;

  base_foraging_fsm(const base_foraging_fsm& fsm) = delete;
  base_foraging_fsm& operator=(const base_foraging_fsm& fsm) = delete;

  /**
   * @brief (Re)-initialize the FSM.
   */
  void init(void) override;

  /**
   * @brief Get a reference to the \ref base_foraging_sensors.
   *
   * Classes needing to reference these sensors should use this function rather
   * than maintaining their own std::shared_ptr copy of things, as that can
   * cause nasty bugs involving things set by the arena loop functions such as
   * tick, location, etc., and that do not get propagated down the
   * composition/inheritance hierarchy of robot controllers properly.
   */
  controller::base_foraging_sensors* base_sensors(void) const {
    return m_sensors.get();
  }

 protected:
  double dir_change_thresh(void) const { return mc_dir_change_thresh; }

  /**
   * @brief Randomize the angle of a vector, for use in change robot heading
   *
   * @param vector The input vector
   *
   * @return The same vector, but with a new angle.
   */
  argos::CVector2 randomize_vector_angle(argos::CVector2 vector);
  controller::actuator_manager* actuators(void) const {
    return m_actuators.get();
  }
  controller::kinematics_calculator& kinematics(void) { return m_kinematics; }

  /**
   * @brief Robots entering this state will return to the nest.
   *
   * This state MUST have a parent state defined that is not
   * \ref task_allocation::hfsm::top_state().
   *
   * Upon return to the nest, a \ref foraging_signal::BLOCK_DROP
   * signal will be returned to the parent state. No robot should return to the
   * nest unless it has a block (duh).
   */
  HFSM_STATE_DECLARE(base_foraging_fsm,
                     transport_to_nest,
                     state_machine::event_data);

  /**
   * @brief Robots entering this state will leave the nest (they are assumed to
   * already be in the nest when this state is entered).
   *
   * This state MUST have a parent state defined that is not \ref
   * \ref task_allocation.hfsm::top_state().
   *
   * When the robot has actually left the nest, according to sensor readings, a
   * \ref foraging_signal::LEFT_NEST signal is returned to the
   * parent state.
   */
  HFSM_STATE_DECLARE(base_foraging_fsm, leaving_nest, state_machine::event_data);

  /**
   * @brief Robots entering this state perform collision avoidance.
   *
   * Robots remain in this state until their FOV is clear of obstacles
   * (additional obstacles many come into view as they avoid the first one). All
   * signals are ignored in this state, so this state can use the default
   * parent. Avoidance is performed by setting robot heading in the opposite
   * direction as the average location of the detected obstacle, and then moving
   * in that direction.
   *
   * After completing avoidance, robots will return to whatever state they were
   * in prior to this one.
   */
  HFSM_STATE_DECLARE_ND(base_foraging_fsm, collision_avoidance);

  /**
   * @brief Robots entering this state will randomly change their exploration
   * direction to the specified direction. All signals are ignored in this
   * state. Once the direction change has been accomplished, the robot will
   * transition back to its previous state.
   */
  HFSM_STATE_DECLARE(base_foraging_fsm, new_direction, state_machine::event_data);

  /**
   * @brief A simple entry state for returning to nest, used to set LED colors
   * for visualization purposes.
   */
  HFSM_ENTRY_DECLARE_ND(base_foraging_fsm, entry_transport_to_nest);

  /**
   * @brief A simple entry state for collision avoidance, used to set LED colors
   * for visualization purposes.
   */
  HFSM_ENTRY_DECLARE_ND(base_foraging_fsm, entry_collision_avoidance);

  /**
   * @brief A simple entry state for leaving nest, used to set LED colors for
   * visualization purposes.
   */
  HFSM_ENTRY_DECLARE_ND(base_foraging_fsm, entry_leaving_nest);

  /**
   * @brief Simple state for entry into the new direction state, used to change
   * LED color for visualization purposes.
   */
  HFSM_ENTRY_DECLARE_ND(base_foraging_fsm, entry_new_direction);

  /**
   * @brief Simple state for entry into the "wait for signal" state, used to
   * change LED color for visualization purposes.
   */
  HFSM_ENTRY_DECLARE_ND(base_foraging_fsm, entry_wait_for_signal);

 private:
  /**
   * @brief When changing direction, a robot is spinning at such a speed that it
   * may overshoot its desired new direction, but as long as it does not
   * overshoot by more than this tolerance, the direction change will still be
   * considered to have occurred successfully.
   */
  static constexpr double kDIR_CHANGE_TOL = 0.25;

  /**
   * @brief When changing direction, it may not be enough to have an arrival
   * tolerance for the new heading; it is possible that given the new direction,
   * the robot's initial heading, and the spinning speed, and it is impossible
   * for the robot to arrive within tolerance of the desired new direction. So,
   * I also define a max number of steps that the robot will spin as a secondary
   * safeguard.
   *
   * Not doing this leads to robots that will spin more or less indefinitely
   * when changing direction on occasion.
   */
  static constexpr uint kDIR_CHANGE_MAX_STEPS = 10;

  // clang-format off
  const double                                       mc_dir_change_thresh;
  uint                                               m_new_dir_count{0};
  argos::CRadians                                    m_new_dir;
  argos::CRandom::CRNG*                              m_rng;
  std::shared_ptr<controller::base_foraging_sensors> m_sensors;
  std::shared_ptr<controller::actuator_manager>      m_actuators;
  controller::kinematics_calculator                  m_kinematics;
  // clang-format on
};

NS_END(fsm, fordyca);

#endif /* INCLUDE_FORDYCA_FSM_BASE_FORAGING_FSM_HPP_ */
