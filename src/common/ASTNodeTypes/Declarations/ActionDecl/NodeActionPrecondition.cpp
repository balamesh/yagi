/**
 * @file   NodeActionPrecondition.cpp
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * AST node for action preconditions.
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

