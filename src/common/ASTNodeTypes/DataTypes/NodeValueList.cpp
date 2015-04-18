/**
 * @file   NodeValueList.cpp
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * AST node for value lists.
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
