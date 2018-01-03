/**
 * @file actuator_parser.hpp
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

#ifndef INCLUDE_FORDYCA_PARAMS_ACTUATOR_PARSER_HPP_
#define INCLUDE_FORDYCA_PARAMS_ACTUATOR_PARSER_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <argos3/core/utility/configuration/argos_configuration.h>
#include "rcppsw/common/common.hpp"
#include "fordyca/params/actuator_params.hpp"
#include "rcppsw/common/xml_param_parser.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca, params);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @class actuator_parser
 * @ingroup params
 *
 * @brief Parses XML parameters for \ref actuator_manager into
 * \ref actuator_params.
 */
class actuator_parser : public rcppsw::common::xml_param_parser {
 public:
  actuator_parser(void) : m_params() {}

  void parse(argos::TConfigurationNode& node) override;
  const struct actuator_params* get_results(void) override { return m_params.get(); }
  void show(std::ostream& stream) override;
  bool validate(void) override;

 private:
  std::unique_ptr<struct actuator_params> m_params;
};

NS_END(params, fordyca);

#endif /* INCLUDE_FORDYCA_PARAMS_ACTUATOR_PARSER_HPP_ */
