/**
 * @file block_transport_metrics_collector.hpp
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

#ifndef INCLUDE_FORDYCA_METRICS_BLOCK_TRANSPORT_METRICS_COLLECTOR_HPP_
#define INCLUDE_FORDYCA_METRICS_BLOCK_TRANSPORT_METRICS_COLLECTOR_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "rcppsw/metrics/base_metrics_collector.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca, metrics);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @class block_transport_metrics_collector
 * @ingroup metrics fsm
 *
 * @brief Collector for \ref block_transport_metrics.
 *
 * Metrics are written out at the end of the specified interval.
 */
class block_transport_metrics_collector : public rcppsw::metrics::base_metrics_collector {
 public:
  /**
   * @param ofname Output file name.
   * @param interval The collection interval.
   */
  block_transport_metrics_collector(const std::string& ofname, uint interval);

  void reset(void) override;
  void reset_after_interval(void) override;
  void reset_after_timestep(void) override;
  void collect(const rcppsw::metrics::base_metrics& metrics) override;

 private:
  struct stats {
    uint n_transporting_to_nest;
    uint n_transporting_to_cache;
    uint n_avoiding_collision;

    uint n_cum_transporting_to_nest;
    uint n_cum_transporting_to_cache;
    uint n_cum_avoiding_collision;
  };

  std::string csv_header_build(const std::string& header) override;
  bool csv_line_build(std::string& line) override;

  struct stats m_stats;
};

NS_END(metrics, fordyca);

#endif /* INCLUDE_FORDYCA_METRICS_BLOCK_TRANSPORT_METRICS_COLLECTOR_HPP_ */
