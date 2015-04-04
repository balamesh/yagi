/**
 * @file   NodeTuple.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for YAGI tuples
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
