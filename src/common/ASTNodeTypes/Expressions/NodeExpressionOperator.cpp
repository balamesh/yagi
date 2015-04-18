/**
 * @file   NodeExpressionOperator.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for the expression operator
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
