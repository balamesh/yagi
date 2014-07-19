/*
 * NodeValueList.cpp
 *
 *  Created on: Jun 5, 2014
 *      Author: cmaier
 */

#include "NodeValueList.h"

NodeValueList::NodeValueList()
{
}

NodeValueList::~NodeValueList()
{
}

bool NodeValueList::isPassedTypeValid(const std::shared_ptr<ASTNodeBase>& valueToAdd)
{
  auto var = std::dynamic_pointer_cast<NodeVariable>(valueToAdd);
  if (var != nullptr)
    return true;

  auto str = std::dynamic_pointer_cast<NodeString>(valueToAdd);
  if (str != nullptr)
    return true;

  return false;
}

void NodeValueList::addValue(const std::shared_ptr<ASTNodeBase<>>& value)
{
  if (isPassedTypeValid(value))
    values_.push_back(value);
  else
    throw std::runtime_error("Invalid Type passed to ValueList!");
}
