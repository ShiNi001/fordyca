/**
 * @file occupancy_grid_parser.hpp
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

#ifndef INCLUDE_FORDYCA_PARAMS_DEPTH0_OCCUPANCY_GRID_PARSER_HPP_
#define INCLUDE_FORDYCA_PARAMS_DEPTH0_OCCUPANCY_GRID_PARSER_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <argos3/core/utility/configuration/argos_configuration.h>

#include "rcppsw/common/common.hpp"
#include "fordyca/params/depth0/occupancy_grid_params.hpp"
#include "rcppsw/common/xml_param_parser.hpp"
#include "fordyca/params/grid_parser.hpp"
#include "fordyca/params/depth0/pheromone_parser.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(fordyca, params, depth0);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @class occupancy_grid_parser
 * @ingroup params depth0
 *
 * @brief Parses XML parameters for \ref occupancy_grid into
 * \ref occupancy_grid_params.
 */
class occupancy_grid_parser: public rcppsw::common::xml_param_parser {
 public:
  occupancy_grid_parser(void): m_params(), m_grid_parser(),
                                    m_pheromone_parser() {}

  void parse(argos::TConfigurationNode& node) override;
  const struct occupancy_grid_params* get_results(void) override {
    return m_params.get();
  }
  void show(std::ostream& stream) override;
  bool validate(void) override;

 private:
  std::unique_ptr<struct occupancy_grid_params> m_params;
  grid_parser m_grid_parser;
  pheromone_parser m_pheromone_parser;
};

NS_END(depth0, params, fordyca);

#endif /* INCLUDE_FORDYCA_PARAMS_DEPTH0_OCCUPANCY_GRID_PARSER_HPP_ */
