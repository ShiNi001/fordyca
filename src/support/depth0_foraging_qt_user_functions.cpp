/**
 * @file depth0_foraging_qt_user_functions.cpp
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
#include <argos3/core/simulator/entity/controllable_entity.h>
#include "fordyca/support/depth0_foraging_qt_user_functions.hpp"
#include "fordyca/controller/depth0_foraging_controller.hpp"
#include "fordyca/representation/line_of_sight.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca, support);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
depth0_foraging_qt_user_functions::depth0_foraging_qt_user_functions() {
  RegisterUserFunction<depth0_foraging_qt_user_functions,
                       argos::CFootBotEntity>(&depth0_foraging_qt_user_functions::Draw);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void depth0_foraging_qt_user_functions::Draw(argos::CFootBotEntity& c_entity) {
  random_foraging_qt_user_functions::Draw(c_entity);

  controller::base_foraging_controller& controller =
      dynamic_cast<controller::base_foraging_controller&>(
          c_entity.GetControllableEntity().GetController());

  if (controller.display_los()) {
    const representation::line_of_sight* los = controller.los();
    DrawCircle(argos::CVector3(0, 0, 0),
               argos::CQuaternion(),
               (los->sizex()/2.0)*0.2,
               argos::CColor::RED,
               false);
  }
}

using namespace argos;
REGISTER_QTOPENGL_USER_FUNCTIONS(depth0_foraging_qt_user_functions,
                                 "depth0_foraging_qt_user_functions")

NS_END(support, fordyca);