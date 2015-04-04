/**
 * @file   NodeBlock.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for a block of statements
 */

#include "NodeBlock.h"

NodeBlock::NodeBlock()
{
}

NodeBlock::~NodeBlock()
{
}

void NodeBlock::replaceStatement(std::shared_ptr<NodeStatementBase>& statement, int idx)
{
  statements_[idx] = statement;
}
