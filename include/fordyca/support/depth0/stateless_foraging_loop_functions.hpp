/**
 * @file stateless_foraging_loop_functions.hpp
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

#ifndef INCLUDE_FORDYCA_SUPPORT_DEPTH0_STATELESS_FORAGING_LOOP_FUNCTIONS_HPP_
#define INCLUDE_FORDYCA_SUPPORT_DEPTH0_STATELESS_FORAGING_LOOP_FUNCTIONS_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "rcppsw/common/common.hpp"
#include "fordyca/representation/arena_map.hpp"
#include "fordyca/support/base_foraging_loop_functions.hpp"
#include "rcppsw/metrics/collector_group.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca);
namespace params { struct output_params; class loop_function_repository; }

NS_START(support, depth0);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * @class statless_foraging_loop_functions
 * @ingroup support depth0
 *
 * @brief Contains the simulation support functions for stateless foraging:
 *
 * - Sending robots block pickup/block drop signals if they are waiting for
 *   them.
 * - Handling block distribution.
 */
class stateless_foraging_loop_functions : public base_foraging_loop_functions,
                                          public rcppsw::er::client {
 public:
  stateless_foraging_loop_functions(void);
  ~stateless_foraging_loop_functions(void) override;

  void Init(argos::TConfigurationNode& node) override;
  void Reset() override;
  void Destroy() override;
  void PreStep() override;

 protected:
  const std::shared_ptr<representation::arena_map>& arena_map(void) const { return m_arena_map; }
  std::shared_ptr<representation::arena_map>& arena_map(void) { return m_arena_map; }

  rcppsw::metrics::collector_group& collector_group(void) { return m_collector_group; }

  const argos::CRange<double>& nest_xrange(void) const { return m_nest_x; }
  const argos::CRange<double>& nest_yrange(void) const { return m_nest_y; }
  virtual void pre_step_final(void);
  std::string log_timestamp_calc(void);
  const std::string& metrics_path(void) const { return m_metrics_path; }

  template<typename T>
  void set_robot_tick(argos::CFootBotEntity& robot) {
    auto& controller = dynamic_cast<T&>(robot.GetControllableEntity().GetController());
    controller.tick(GetSpace().GetSimulationClock());
  }

 private:
  void arena_map_init(params::loop_function_repository& repo);
  void output_init(const struct params::output_params* p_output);
  void metric_collecting_init(const struct params::output_params* p_output);
  void pre_step_iter(argos::CFootBotEntity& robot);
  argos::CColor GetFloorColor(const argos::CVector2& plane_pos) override;

  // clang-format off
  argos::CRange<double>                      m_nest_x;
  argos::CRange<double>                      m_nest_y;
  std::string                                m_output_root;
  std::string                                m_metrics_path;

  rcppsw::metrics::collector_group           m_collector_group;
  std::shared_ptr<representation::arena_map> m_arena_map;
  // clang-format on
};

NS_END(depth0, support, fordyca);

#endif /* INCLUDE_FORDYCA_SUPPORT_DEPTH0_STATELESS_FORAGING_LOOP_FUNCTIONS_HPP_ */
