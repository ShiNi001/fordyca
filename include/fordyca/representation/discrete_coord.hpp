/**
 * @file discrete_coord.hpp
 * @ingroup representation
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

#ifndef INCLUDE_FORDYCA_REPRESENTATION_DISCRETE_COORD_HPP_
#define INCLUDE_FORDYCA_REPRESENTATION_DISCRETE_COORD_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <utility>
#include "rcppsw/common/common.hpp"
#include <argos3/core/utility/math/vector2.h>

/*******************************************************************************
 * namespaces
 ******************************************************************************/
NS_START(fordyca, representation);

/*******************************************************************************
 * Type Definitions
 ******************************************************************************/
using discrete_coord = std::pair<size_t, size_t>;

/*******************************************************************************
 * Functions
 ******************************************************************************/
/**
 * @brief Translate real (continuous) coordinates to discrete ones using the
 * specified resolution.
 */
discrete_coord real_to_discrete_coord(const argos::CVector2& r_coord,
                                      double resolution);

/**
 * @brief Translate discrete coordinates to real (continuous) ones using the
 * specified resolution.
 */
argos::CVector2 discrete_to_real_coord(const discrete_coord& d_coord,
                                       double resolution);

NS_END(representation, fordyca);

#endif /* INCLUDE_FORDYCA_REPRESENTATION_DISCRETE_COORD_HPP_ */
