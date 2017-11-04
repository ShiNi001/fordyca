/**
 * @file cache_params.hpp
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

#ifndef INCLUDE_FORDYCA_PARAMS_CACHE_PARAMS_HPP_
#define INCLUDE_FORDYCA_PARAMS_CACHE_PARAMS_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "rcppsw/common/base_params.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca, params);

/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
struct cache_params : public rcppsw::common::base_params {
  cache_params(void) : create_static_cache(false),
                       create_dynamic_caches(false),
                       static_cache_size(0),
                       dimension(0.0),
                       min_dist(0.0) {}

  bool create_static_cache;
  bool create_dynamic_caches;
  uint static_cache_size;
  double dimension;
  double min_dist;
};

NS_END(params, fordyca);

#endif /* INCLUDE_FORDYCA_PARAMS_CACHE_PARAMS_HPP_ */
