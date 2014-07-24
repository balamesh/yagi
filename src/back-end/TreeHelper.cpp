/*
 * TreeHelper.cpp
 *
 *  Created on: Jul 23, 2014
 *      Author: cmaier
 */
#include "TreeHelper.h"

namespace yagi {
namespace treeHelper {

bool isValueNode(ASTNodeBase<>* node)
{
  return (dynamic_cast<NodeString*>(node) || dynamic_cast<NodeVariable*>(node));
}

std::string getValueFromValueNode(ASTNodeBase<>* valueNode, ASTNodeVisitorBase& ctx)
{
  auto res = valueNode->accept(ctx).get<std::string>();

  //it is a <string>
  if (dynamic_cast<NodeString*>(valueNode))
  {
    return res;
  }
  else if (dynamic_cast<NodeVariable*>(valueNode))
  {
    return yagi::execution::VariableTableManager::getInstance().getMainVariableTable().getVariableValue(
        res);
  }
  else
  {
    throw std::runtime_error(
        "getValueFromValueNode called with something that is neither a <string> nor a <variable>");
  }
}

}
}
