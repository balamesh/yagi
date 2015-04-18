/**
 * @file   TreeHelper.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Helper functions for the AST
 */

#include "TreeHelper.h"

#include <stdexcept>
#include <string>

#include "../common/ASTNodeTypes/ASTNodeBase.h"
#include "../common/ASTNodeTypes/DataTypes/NodeString.h"
#include "../common/ASTNodeTypes/Variables/NodeVariable.h"
#include "../utils/Any.h"
#include "Variables/VariableTable.h"

namespace yagi {
namespace treeHelper {

bool isValueNode(ASTNodeBase<>* node)
{
  return (dynamic_cast<NodeString*>(node) || dynamic_cast<NodeVariable*>(node));
}

std::string getValueFromValueNode(ASTNodeBase<>* valueNode, ASTNodeVisitorBase& ctx,
    yagi::execution::VariableTable* varTable)
{
  auto res = valueNode->accept(ctx).get<std::string>();

  //it is a <string>
  if (dynamic_cast<NodeString*>(valueNode))
  {
    return res;
  }
  else if (dynamic_cast<NodeVariable*>(valueNode))
  {
    return varTable->getVariableValue(res);
  }
  else
  {
    throw std::runtime_error(
        "getValueFromValueNode called with something that is neither a <string> nor a <variable>");
  }
}

}
}
