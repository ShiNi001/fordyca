/**
 * @file depth0_foraging_controller.cpp
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

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fordyca/controller/depth0_foraging_controller.hpp"
#include <argos3/plugins/robots/generic/control_interface/ci_range_and_bearing_sensor.h>
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_proximity_sensor.h>
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_light_sensor.h>
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_motor_ground_sensor.h>

#include "rcppsw/common/er_server.hpp"
#include "fordyca/params/fsm_params.hpp"
#include "fordyca/params/perceived_grid_params.hpp"
#include "fordyca/params/sensor_params.hpp"
#include "fordyca/params/depth0_foraging_repository.hpp"
#include "fordyca/representation/line_of_sight.hpp"
#include "fordyca/events/block_found.hpp"
#include "fordyca/events/cache_found.hpp"
#include "fordyca/events/cell_empty.hpp"
#include "fordyca/controller/depth1_foraging_sensors.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca, controller);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void depth0_foraging_controller::robot_loc(argos::CVector2 loc) {
  m_sensors->robot_loc(loc);
}

argos::CVector2 depth0_foraging_controller::robot_loc(void) const {
  return m_sensors->robot_loc();
}

void depth0_foraging_controller::tick(uint tick) {
  m_sensors->tick(tick);
} /* tick() */

__pure const representation::line_of_sight* depth0_foraging_controller::los(void) const {
  return m_sensors->los();
}
void depth0_foraging_controller::los(
    std::unique_ptr<representation::line_of_sight>& new_los) {
  m_sensors->los(new_los);
}

void depth0_foraging_controller::ControlStep(void) {
  /*
   * Update the perceived arena map with the current line-of-sight, and update
   * the relevance of information within it. Then, you can run the main FSM
   * loop.
   */
  process_los(m_sensors->los());
  m_map->update_density();
  if (m_fsm->task_finished()) {
    m_fsm->task_reset();
    m_fsm->task_start(nullptr);
  } else {
    m_fsm->task_execute();
  }
} /* ControlStep() */

void depth0_foraging_controller::Init(argos::TConfigurationNode& node) {
  params::depth0_foraging_repository param_repo;

  base_foraging_controller::Init(node);
  ER_NOM("Initializing depth0_foraging controller");
  param_repo.parse_all(node);
  param_repo.show_all(server_handle()->log_stream());

  m_map.reset(new representation::perceived_arena_map(
      server(),
      static_cast<const struct params::perceived_grid_params*>(
          param_repo.get_params("perceived_grid")),
      GetId()));

  m_sensors.reset(new depth1_foraging_sensors(
      static_cast<const struct params::sensor_params*>(
          param_repo.get_params("sensors")),
      GetSensor<argos::CCI_RangeAndBearingSensor>("range_and_bearing"),
      GetSensor<argos::CCI_FootBotProximitySensor>("footbot_proximity"),
      GetSensor<argos::CCI_FootBotLightSensor>("footbot_light"),
      GetSensor<argos::CCI_FootBotMotorGroundSensor>("footbot_motor_ground")));

  m_fsm.reset(
      new fsm::depth0_foraging_fsm(static_cast<const struct params::fsm_params*>(
          param_repo.get_params("fsm")),
                                   server(),
                                   m_sensors,
                                   base_foraging_controller::actuators(),
                                   m_map));

  ER_NOM("depth0_foraging controller initialization finished");
} /* Init() */

void depth0_foraging_controller::process_los(const representation::line_of_sight* const los) {
  for (auto block : los->blocks()) {
    if (!m_map->access(block->discrete_loc().first,
                       block->discrete_loc().second).state_has_block()) {
      events::block_found op(base_foraging_controller::server(), block,
                             block->discrete_loc().first,
                             block->discrete_loc().second);
      m_map->accept(op);
      ER_NOM("Discovered block%d at (%zu, %zu)", block->id(),
             block->discrete_loc().first, block->discrete_loc().second);
    }
  } /* for(block..) */
  for (auto cache : los->caches()) {
    if (!m_map->access(cache->discrete_loc().first,
                       cache->discrete_loc().second).state_has_cache()) {
      events::cache_found op(base_foraging_controller::server(), cache,
                             cache->discrete_loc().first,
                             cache->discrete_loc().second);
      m_map->accept(op);
      ER_NOM("Discovered cache%d at (%zu, %zu)", cache->id(),
             cache->discrete_loc().first, cache->discrete_loc().second);
    }
  } /* for(cache..) */
} /* process_los() */

/*******************************************************************************
 * Base Diagnostics
 ******************************************************************************/
bool depth0_foraging_controller::is_exploring_for_block(void) const {
  return m_fsm->is_exploring_for_block();
} /* is_exploring */

bool depth0_foraging_controller::is_avoiding_collision(void) const {
  return m_fsm->is_avoiding_collision();
} /* is_avoiding_collision() */

bool depth0_foraging_controller::is_transporting_to_nest(void) const {
  return m_fsm->is_transporting_to_nest();
} /* is_transporting_to_nest() */

/*******************************************************************************
 * Depth0 Diagnostics
 ******************************************************************************/
bool depth0_foraging_controller::is_acquiring_block(void) const {
  return m_fsm->is_acquiring_block();
} /* is_acquiring_block() */

bool depth0_foraging_controller::is_vectoring_to_block(void) const {
  return m_fsm->is_vectoring_to_block();
} /* is_vectoring_to_block() */


using namespace argos;
REGISTER_CONTROLLER(depth0_foraging_controller, "depth0_foraging_controller")

NS_END(controller, fordyca);