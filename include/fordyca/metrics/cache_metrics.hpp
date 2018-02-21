/**
 * @file cache_metrics.hpp
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

#ifndef INCLUDE_FORDYCA_METRICS_CACHE_METRICS_HPP_
#define INCLUDE_FORDYCA_METRICS_CACHE_METRICS_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "rcppsw/metrics/base_metrics.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca, metrics, collectible_metrics);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * @class cache_metrics
 * @ingroup metrics
 *
 * @brief Interface defining collectible metrics on static/dynamic caches in the
 * arena.
 */
class cache_metrics : public rcppsw::metrics::base_metrics {
 public:
  cache_metrics(void) = default;
  ~cache_metrics(void) override = default;
  cache_metrics(const cache_metrics&) = default;
  cache_metrics& operator=(const cache_metrics&) = default;

  /**
   * @brief Get the # of blocks currently in the cache (independent of any
   * calls to \ref reset_metrics()).
   */
  virtual uint n_blocks(void) const = 0;

  /**
   * @brief Get the # of blocks that have been picked up from the cache since
   * the last call to \ref reset_metrics().
   */
  virtual uint n_block_pickups(void) const = 0;

  /**
   * @brief Get the # of blocks that have been dropped in the cache since the
   * last call to \ref reset_metrics().
   */
  virtual uint n_block_drops(void) const = 0;

  /**
   * @brief Get the cumulative duration of all penalties served for the cache
   * since the last call to \ref reset_metrics().
   */
  virtual uint penalties_served(void) const = 0;

  /**
   * @brief Reset all gathered metrics to their initial state after some
   * interval of time has passed.
   */
  virtual void reset_metrics(void) = 0;
};

NS_END(collectible_metrics, metrics, fordyca);

#endif /* INCLUDE_FORDYCA_METRICS_CACHE_METRICS_HPP_ */
