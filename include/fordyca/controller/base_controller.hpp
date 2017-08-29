/**
 * @file base_controller.hpp
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

#ifndef INCLUDE_FORDYCA_CONTROLLER_BASE_CONTROLLER_HPP_
#define INCLUDE_FORDYCA_CONTROLLER_BASE_CONTROLLER_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <argos3/core/control_interface/ci_controller.h>
#include <argos3/core/utility/math/rng.h>
#include <boost/shared_ptr.hpp>
#include "fordyca/controller/foraging_fsm.hpp"
#include "fordyca/controller/sensor_manager.hpp"
#include "fordyca/controller/actuator_manager.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca, controller);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief  A controller is simply an implementation of the CCI_Controller class.
 */
class base_controller : public argos::CCI_Controller,
                            public rcppsw::common::er_client {
 public:
  enum event_type {
    FSM_START,
    BLOCK_FOUND
  };

  base_controller(void) :
      er_client(),
      m_display_id(false),
      m_block(nullptr),
      m_server(new rcppsw::common::er_server("controller-init.txt")),
      m_actuators(),
      m_sensors(),
      m_fsm() {}

  bool is_exploring(void) const { return m_fsm->is_exploring(); }
  bool is_returning(void) const { return m_fsm->is_returning(); }
  bool is_avoiding_collision(void) const { return m_fsm->is_avoiding_collision(); }
  bool in_nest(void) const { return m_sensors->in_nest(); }
  bool block_detected(void) const { return m_sensors->block_detected(); }
  void publish_event(enum event_type event);
  void display_id(bool display_id) { m_display_id = display_id; }
  bool display_id(void) const { return m_display_id; }

  /*
   * @brief Initialize the controller.
   *
   * @param t_node Points to the <parameters> section in the XML file in the
   *               <controllers><base_controller_controller> section.
   */
  virtual void Init(argos::TConfigurationNode& t_node);

  /*
   * @brief Called once every time step; length set in the XML file.
   *
   * Since the FSM does most of the work, this function just tells it run.
   */
  virtual void ControlStep(void) { m_fsm->run(); }

  /*
   * @brief Reset controller to its state right after the Init().
   */
  virtual void Reset(void);

  /*
   * @brief Cleanup whatever was done by Init().
   */
  virtual void Destroy(void) {}

  /**
   * @brief Return if the robot is currently carrying a block.
   */
  bool is_carrying_block(void) const { return nullptr != m_block; }

  /**
   * @brief Return the block robot is carrying.
   */
  representation::block* block(void) const { return m_block; }

  /**
   * @brief Drop a carried block in the nest, updating state as appropriate.
   *
   * This needs to be here, rather than in the FSM, because dropping of blocks
   * needs to be done in the loop functions so the area can correctly be drawn
   * each timestep.
   */
  virtual void drop_block_in_nest(void);

  /**
   * @brief Pickup a block the robot is currently on top of, updating state as appropriate.
   *
   * This needs to be here, rather than in the FSM, because picking up blocks
   * needs to be handled in the loop functions so the area can correctly be drawn
   * each timestep.
   */
  virtual void pickup_block(representation::block* block);

 protected:
  sensor_manager* sensors(void) const { return m_sensors.get(); }

 private:
  base_controller(const base_controller& other) = delete;
  base_controller& operator=(const base_controller& other) = delete;

  bool                                       m_display_id;
  representation::block*                     m_block;
  std::shared_ptr<rcppsw::common::er_server> m_server;
  std::shared_ptr<actuator_manager>          m_actuators;
  std::shared_ptr<sensor_manager>            m_sensors;
  std::unique_ptr<foraging_fsm>              m_fsm;
};

NS_END(controller, fordyca);

#endif /* INCLUDE_FORDYCA_BASE_CONTROLLER_CONTROLLER_HPP_ */