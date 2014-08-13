/*
 * NodeBlock.cpp
 *
 *  Created on: Jun 4, 2014
 *      Author: cmaier
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
