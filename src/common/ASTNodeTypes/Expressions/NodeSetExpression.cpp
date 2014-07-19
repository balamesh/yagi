/*
 * NodeSetExpression.cpp
 *
 *  Created on: May 27, 2014
 *      Author: cmaier
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

