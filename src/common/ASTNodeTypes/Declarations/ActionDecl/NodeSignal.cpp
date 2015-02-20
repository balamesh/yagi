/**
 * @file   NodeSignal.cpp
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * AST node for action signal.
 */

#include "NodeSignal.h"

NodeSignal::NodeSignal() :
    signalData_(nullptr)
{
}

NodeSignal::NodeSignal(const std::shared_ptr<NodeValueExpression>& signalExpr) :
    signalData_(signalExpr)
{
}

NodeSignal::~NodeSignal()
{
}

