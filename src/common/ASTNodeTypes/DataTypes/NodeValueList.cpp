/*
 * NodeValueList.cpp
 *
 *  Created on: Jun 5, 2014
 *      Author: cmaier
 */

#include "NodeValueList.h"

NodeValueList::NodeValueList()
{
  // TODO Auto-generated constructor stub

}

NodeValueList::~NodeValueList()
{
  // TODO Auto-generated destructor stub
}

bool NodeValueList::isPassedTypeValid(const std::shared_ptr<ASTNodeBase>& valueToAdd)
{
  auto var = std::dynamic_pointer_cast<NodeVariable>(valueToAdd);
  if (var != nullptr) return true;

  auto integer = std::dynamic_pointer_cast<NodeInteger>(valueToAdd);
  if (integer != nullptr) return true;

  auto str = std::dynamic_pointer_cast<NodeString>(valueToAdd);
  if (str != nullptr) return true;

  return false;
}

