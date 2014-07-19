/*
 * ValueExpressionOperator.cpp
 *
 *  Created on: May 26, 2014
 *      Author: cmaier
 */

#include "NodeValueExpressionOperator.h"

NodeValueExpressionOperator::NodeValueExpressionOperator() :
    operator_(ValueExprOperator::Unknown)
{
}

NodeValueExpressionOperator::~NodeValueExpressionOperator()
{
}

void NodeValueExpressionOperator::fromString(const std::string& opString)
{
  if (opString == "+")
    operator_ = ValueExprOperator::Plus;
  else if (opString == "-")
    operator_ = ValueExprOperator::Minus;
  else
    throw std::runtime_error("Invalid operator string '" + opString + "'!");
}

std::string NodeValueExpressionOperator::toString()
{
  if (operator_ == ValueExprOperator::Plus)
    return "+";
  else if (operator_ == ValueExprOperator::Minus)
    return "-";
  else
    throw std::runtime_error("Val Expr Op is unknown!");
}
