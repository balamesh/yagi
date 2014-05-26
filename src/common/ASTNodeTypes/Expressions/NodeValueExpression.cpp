/*
 * ValueExpression.cpp
 *
 *  Created on: May 26, 2014
 *      Author: cmaier
 */

#include "NodeValueExpression.h"

NodeValueExpression::NodeValueExpression()
{
  // TODO Auto-generated constructor stub
  operator_ = nullptr;
  lhs_ = nullptr;
  rhs_ = nullptr;

}

NodeValueExpression::~NodeValueExpression()
{
  // TODO Auto-generated destructor stub
}

bool NodeValueExpression::IsPassedTypeValid(const std::shared_ptr<ASTNodeBase>& valueToAssign)
{
  //type must be either String, Integer, Variable or NodeValueExpression
  auto stringVal = std::static_pointer_cast<NodeString>(valueToAssign);
  if (stringVal != nullptr) return true;

  auto intVal = std::static_pointer_cast<NodeInteger>(valueToAssign);
  if (intVal != nullptr) return true;

  auto var = std::static_pointer_cast<NodeVariable>(valueToAssign);
  if (var != nullptr) return true;

  auto valExpr = std::static_pointer_cast<NodeValueExpression>(valueToAssign);
  if (valExpr != nullptr) return true;

  return false;
}

