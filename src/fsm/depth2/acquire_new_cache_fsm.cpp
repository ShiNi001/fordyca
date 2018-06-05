/**
 * @file acquire_new_cache_fsm.cpp
 *
 * @copyright 2018 John Harwell, All rights reserved.
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
#include "fordyca/fsm/depth2/acquire_new_cache_fsm.hpp"

#include "fordyca/controller/depth2/new_cache_selector.hpp"
#include "fordyca/representation/base_cache.hpp"
#include "fordyca/representation/perceived_arena_map.hpp"
#include "fordyca/controller/base_sensing_subsystem.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca, fsm, depth2);
namespace state_machine = rcppsw::patterns::state_machine;
namespace depth1 = controller::depth1;

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
acquire_new_cache_fsm::acquire_new_cache_fsm(
    const struct params::fsm_params* params,
    const std::shared_ptr<rcppsw::er::server>& server,
    const std::shared_ptr<controller::saa_subsystem>& saa,
    std::shared_ptr<const representation::perceived_arena_map> map)
    : acquire_cache_fsm(params, server, saa, map) {}

/*******************************************************************************
 * General Member Functions
 ******************************************************************************/
argos::CVector2 acquire_new_cache_fsm::select_cache_for_acquisition(void) {
  controller::depth2::new_cache_selector selector(server_ref(),
                                                  nest_center());

  /* A "new" cache is the same as a single block  */
  representation::perceived_block best =
      selector.calc_best(map()->perceived_blocks(), base_sensors()->position());
  ER_NOM("Select new cache for acquisition: %d@(%zu, %zu) [utility=%f]",
         best.ent->id(),
         best.ent->discrete_loc().first,
         best.ent->discrete_loc().second,
         best.density.last_result());
  return best.ent->real_loc();
} /* select_cache() */

NS_END(depth2, controller, fordyca);