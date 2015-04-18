/**
 * @file   NodeAssignmentOperator.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for assignment operators
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


#include "NodeAssignmentOperator.h"

NodeAssignmentOperator::NodeAssignmentOperator() :
    operator_(AssignmentOperator::Unknown)
{
}

NodeAssignmentOperator::~NodeAssignmentOperator()
{

}

std::string NodeAssignmentOperator::toString()
{
  if (operator_ == AssignmentOperator::Assign)
    return "=";
  else if (operator_ == AssignmentOperator::AddAssign)
    return "+=";
  else if (operator_ == AssignmentOperator::RemoveAssign)
    return "-=";
  else
    return "<unknown>";
}

void NodeAssignmentOperator::fromString(const std::string& opString)
{
  if (opString == "=")
    operator_ = AssignmentOperator::Assign;
  else if (opString == "+=")
    operator_ = AssignmentOperator::AddAssign;
  else if (opString == "-=")
    operator_ = AssignmentOperator::RemoveAssign;
  else
    throw std::runtime_error("Invalid assignment operator string '" + opString + "'!");
}
