/**
 * @file   TreeHelper.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Helper functions for the AST
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
