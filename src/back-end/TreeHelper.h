/**
 * @file   TreeHelper.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Helper functions for the AST
 */

/*
 This file is part of YAGI.

 YAGI is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3.0 of the License, or (at your option) any later version.

 YAGI is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with YAGI.
*/


#ifndef TREEHELPER_H_
#define TREEHELPER_H_

#include <string>

#include "../common/ASTNodeTypes/ASTNodeBase.h"

namespace yagi {
namespace execution {
class VariableTable;
} /* namespace execution */
} /* namespace yagi */

namespace yagi {
namespace treeHelper {

/**
 * Get the value from a value node
 * @param valueNode The ASTNode that represents a value
 * @param ctx The current context
 * @param varTable The current variable table
 * @return The value
 */
std::string getValueFromValueNode(ASTNodeBase<>* valueNode, ASTNodeVisitorBase& ctx,
    yagi::execution::VariableTable* varTable);

/**
 * Check whether or not an AST node represents a value
 * @param node The AST node to check
 * @return True if value node, false otherwise
 */
bool isValueNode(ASTNodeBase<>* node);

}
}

#endif /* TREEHELPER_H_ */
