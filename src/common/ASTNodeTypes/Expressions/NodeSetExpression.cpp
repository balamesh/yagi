/**
 * @file   NodeSetExpression.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for set expressions
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


#include "NodeSetExpression.h"

NodeSetExpression::NodeSetExpression() :
    operator_(nullptr), lhs_(nullptr), rhs_(nullptr)
{

}

NodeSetExpression::~NodeSetExpression()
{

}

bool NodeSetExpression::isPassedTypeValid(const std::shared_ptr<ASTNodeBase>& valueToAssign)
{
  //type must be either a set, an id or an other setexpr
  auto set = std::dynamic_pointer_cast<NodeSet>(valueToAssign);
  if (set != nullptr)
    return true;

  auto id = std::dynamic_pointer_cast<NodeID>(valueToAssign);
  if (id != nullptr)
    return true;

  auto setExpr = std::dynamic_pointer_cast<NodeSetExpression>(valueToAssign);
  if (setExpr != nullptr)
    return true;

  return false;
}

