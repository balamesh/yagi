/**
 * @file   NodeTuple.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for YAGI tuples
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


#include "NodeTuple.h"

NodeTuple::NodeTuple()
{
}

NodeTuple::~NodeTuple()
{
}

bool NodeTuple::isPassedTypeValid(const std::shared_ptr<ASTNodeBase>& tupleVal)
{
  //type must be either a string, a variable, incomplete knowledge or a pattern matching symbol
  auto str = std::dynamic_pointer_cast<NodeString>(tupleVal);
  if (str != nullptr)
    return true;

  auto var = std::dynamic_pointer_cast<NodeVariable>(tupleVal);
  if (var != nullptr)
    return true;

  auto patternMatching = std::dynamic_pointer_cast<NodePatternMatching>(tupleVal);
  if (patternMatching != nullptr)
    return true;

  auto incompleteKnowledge = std::dynamic_pointer_cast<NodeIncompleteKnowledge>(tupleVal);
  if (incompleteKnowledge != nullptr)
    return true;

  return false;
}
