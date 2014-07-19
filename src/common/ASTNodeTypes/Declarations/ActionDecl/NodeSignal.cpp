/*
 * NodeSignal.cpp
 *
 *  Created on: May 23, 2014
 *      Author: cmaier
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

