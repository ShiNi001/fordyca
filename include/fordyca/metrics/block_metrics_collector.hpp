/**
 * @file block_metrics_collector.hpp
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

#ifndef INCLUDE_FORDYCA_METRICS_BLOCK_METRICS_COLLECTOR_HPP_
#define INCLUDE_FORDYCA_METRICS_BLOCK_METRICS_COLLECTOR_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "rcppsw/metrics/base_metrics_collector.hpp"
#include "rcppsw/patterns/visitor/visitable.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca, metrics);
namespace visitor = rcppsw::patterns::visitor;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @class block_metrics_collector
 * @ingroup metrics
 *
 * @brief Collector for \ref block_metrics.
 *
 * Metrics are written out at the specified interval.
 */
class block_metrics_collector
    : public rcppsw::metrics::base_metrics_collector,
      public visitor::visitable_any<block_metrics_collector> {
 public:
  /**
   * @param ofname Output file name.
   * @param interval Collection interval.
   */
  block_metrics_collector(const std::string& ofname, uint interval);

  void reset(void) override;
  void reset_after_interval(void) override;
  void collect(const rcppsw::metrics::base_metrics& metrics) override;
  size_t cum_collected(void) const { return m_metrics.cum_collected; }

 private:
  struct block_metrics {
    uint cum_collected; /* aggregate across blocks, not reset each timestep*/
    uint cum_carries;   /* aggregate across blocks, not reset each timstep */
  };

  std::string csv_header_build(const std::string& header) override;
  bool csv_line_build(std::string& line) override;
  struct block_metrics m_metrics;
};

NS_END(metrics, fordyca);

#endif /* INCLUDE_FORDYCA_METRICS_BLOCK_METRICS_COLLECTOR_HPP_ */
