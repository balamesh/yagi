/*
 * NodeTuple.cpp
 *
 *  Created on: May 28, 2014
 *      Author: cmaier
 */

#include "NodeTuple.h"

NodeTuple::NodeTuple()
{
  // TODO Auto-generated constructor stub
}

NodeTuple::~NodeTuple()
{
  // TODO Auto-generated destructor stub
}

bool NodeTuple::isPassedTypeValid(const std::shared_ptr<ASTNodeBase>& tupleVal)
{
  //type must be either a string, a variable or a pattern matching symbol
  auto str = std::dynamic_pointer_cast<NodeString>(tupleVal);
  if (str != nullptr)
    return true;

  auto var = std::dynamic_pointer_cast<NodeVariable>(tupleVal);
  if (var != nullptr)
    return true;

  //TODO
  //  auto intVal = std::dynamic_pointer_cast<NodeSet>(valueToAssign);
  //  if (intVal != nullptr) return true;

  return false;
}