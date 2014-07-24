/*
 * TreeHelper.h
 *
 *  Created on: Jul 23, 2014
 *      Author: cmaier
 */

#ifndef TREEHELPER_H_
#define TREEHELPER_H_

#include <memory>

#include "Variables/VariableTableManager.h"
#include "../common/ASTNodeTypes/ASTNodeBase.h"
#include "../common/ASTNodeTypes/DataTypes/NodeString.h"
#include "../common/ASTNodeTypes/Variables/NodeVariable.h"

namespace yagi {
namespace treeHelper {

std::string getValueFromValueNode(ASTNodeBase<>* valueNode,
    ASTNodeVisitorBase& ctx);
bool isValueNode(ASTNodeBase<>* node);

}
}

#endif /* TREEHELPER_H_ */
