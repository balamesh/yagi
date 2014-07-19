/*
 * NodeActionPrecondition.cpp
 *
 *  Created on: May 23, 2014
 *      Author: cmaier
 */

#include "NodeActionPrecondition.h"

NodeActionPrecondition::NodeActionPrecondition() :
    formula_(nullptr)
{

}

NodeActionPrecondition::NodeActionPrecondition(const std::shared_ptr<NodeFormulaBase>& formula) :
    formula_(formula)
{
}

NodeActionPrecondition::~NodeActionPrecondition()
{
}

