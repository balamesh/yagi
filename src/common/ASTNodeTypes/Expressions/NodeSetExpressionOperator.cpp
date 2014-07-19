/*
 * NodeSetExpressionOperator.cpp
 *
 *  Created on: May 27, 2014
 *      Author: cmaier
 */

#include "NodeSetExpressionOperator.h"

NodeSetExpressionOperator::NodeSetExpressionOperator() :
    operator_(SetExprOperator::Unknown)
{
}

NodeSetExpressionOperator::~NodeSetExpressionOperator()
{

}

std::string NodeSetExpressionOperator::toString()
{
  if (operator_ == SetExprOperator::Assign)
    return "=";
  else if (operator_ == SetExprOperator::AddAssign)
    return "+=";
  else if (operator_ == SetExprOperator::RemoveAssign)
    return "-=";
  else
    return "<unknown>";
}

void NodeSetExpressionOperator::fromString(const std::string& opString)
{
  if (opString == "=")
    operator_ = SetExprOperator::Assign;
  else if (opString == "+=")
    operator_ = SetExprOperator::AddAssign;
  else if (opString == "-=")
    operator_ = SetExprOperator::RemoveAssign;
  else
    throw std::runtime_error("Invalid set expression operator string '" + opString + "'!");
}
