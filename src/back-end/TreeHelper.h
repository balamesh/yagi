/*
 * TreeHelper.h
 *
 *  Created on: Jul 23, 2014
 *      Author: cmaier
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

std::string getValueFromValueNode(ASTNodeBase<>* valueNode,
    ASTNodeVisitorBase& ctx, yagi::execution::VariableTable* varTable);
bool isValueNode(ASTNodeBase<>* node);

}
}

#endif /* TREEHELPER_H_ */
