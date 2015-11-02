/*
 * This file is part of the Autocalibration Codebase.
 *
 * The Autocalibration Codebase is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The Autocalibration Codebase is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the Autocalibration Codebase.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2013 NUBots <nubots@nubots.net>
 */

#ifndef UTILITY_SUPPORT_yaml_expression_H
#define UTILITY_SUPPORT_yaml_expression_H

#include <iostream>
#include <yaml-cpp/yaml.h>
#include <muParser.h>

namespace utility {
namespace support {
    /**
     * Represents a mathematical expression
     * Acts as a double
     */
    struct Expression {
        double value;
        Expression() : value(0.0) {}
        Expression(double x) : value(x) {}
        operator double() const { return value; }
    };
}
}

namespace YAML {

    template<>
    struct convert<utility::support::Expression> {
        static Node encode(const utility::support::Expression& rhs) {
            Node node;

            // Treat as a double
            node = rhs;

            return node;
        }

        static bool decode(const Node& node, utility::support::Expression& rhs) {

            try {
                // Parse the expression using muParser
                mu::Parser parser;
                parser.DefineConst("pi", double(M_PI));
                parser.SetExpr(node.as<std::string>());
                rhs = parser.Eval();

                return true;
            }
            catch(mu::Parser::exception_type& e) {
                return false;
            }
        }
    };

}

#endif
