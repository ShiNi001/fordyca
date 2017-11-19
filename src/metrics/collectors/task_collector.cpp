/**
 * @file task_collector.cpp
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
#include "fordyca/metrics/collectors/task_collector.hpp"
#include "fordyca/metrics/collectible_metrics/task_metrics.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca, metrics, collectors);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
std::string task_collector::csv_header_build(const std::string& header) {
  return base_metric_collector::csv_header_build(header) +
      "n_collectors;n_foragers;n_generalists";
} /* csv_header_build() */

void task_collector::reset(void) {
  base_metric_collector::reset();
  reset_on_timestep();
} /* reset() */

void task_collector::collect(
    const collectible_metrics::task_metrics& metrics) {
  m_stats.n_collectors += metrics.task_name() == "collector";
  m_stats.n_foragers += metrics.task_name() == "forager";
  m_stats.n_generalists += metrics.task_name() == "generalist";
} /* collect() */

bool task_collector::csv_line_build(std::string& line) {
  line = std::to_string(m_stats.n_collectors) + ";" +
         std::to_string(m_stats.n_foragers) + ";" +
         std::to_string(m_stats.n_generalists);
  return true;
} /* store_foraging_stats() */

void task_collector::reset_on_timestep(void) {
  m_stats = {0, 0, 0};
} /* reset_on_timestep() */

NS_END(collectors, metrics, fordyca);