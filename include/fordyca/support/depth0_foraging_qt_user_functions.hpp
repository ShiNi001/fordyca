/**
 * @file depth0_foraging_qt_user_functions.hpp
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
#ifndef INCLUDE_FORDYCA_SUPPORT_DEPTH0_FORAGING_QT_USER_FUNCTIONS_HPP_
#define INCLUDE_FORDYCA_SUPPORT_DEPTH0_FORAGING_QT_USER_FUNCTIONS_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fordyca/support/random_foraging_qt_user_functions.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca, support);

/*******************************************************************************
 * Classes
 ******************************************************************************/
class depth0_foraging_qt_user_functions : public random_foraging_qt_user_functions {
 public:
  depth0_foraging_qt_user_functions(void);

  virtual ~depth0_foraging_qt_user_functions() {}

  void Draw(argos::CFootBotEntity& c_entity) override;
};

NS_END(fordyca, support);

#endif /* INCLUDE_FORDYCA_SUPPORT_DEPTH0_FORAGING_QT_USER_FUNCTIONS_HPP_ */