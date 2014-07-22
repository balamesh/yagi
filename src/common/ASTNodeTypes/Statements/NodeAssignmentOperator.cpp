/*
 * NodeAssignmentOperator.cpp
 *
 *  Created on: May 27, 2014
 *      Author: cmaier
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
