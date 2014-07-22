/*
 * NodeExpressionOperator.cpp
 *
 *  Created on: May 26, 2014
 *      Author: cmaier
 */

#include "NodeExpressionOperator.h"

NodeExpressionOperator::NodeExpressionOperator() :
    operator_(ExprOperator::Unknown)
{
}

NodeExpressionOperator::~NodeExpressionOperator()
{
}

void NodeExpressionOperator::fromString(const std::string& opString)
{
  if (opString == "+")
    operator_ = ExprOperator::Plus;
  else if (opString == "-")
    operator_ = ExprOperator::Minus;
  else
    throw std::runtime_error("Invalid operator string '" + opString + "'!");
}

std::string NodeExpressionOperator::toString()
{
  if (operator_ == ExprOperator::Plus)
    return "+";
  else if (operator_ == ExprOperator::Minus)
    return "-";
  else
    throw std::runtime_error("Val Expr Op is unknown!");
}
