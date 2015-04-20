/**
 * @file   TreeHelper.cpp
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
