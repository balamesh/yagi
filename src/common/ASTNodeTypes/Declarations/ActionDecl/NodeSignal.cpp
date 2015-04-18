/**
 * @file   NodeSignal.cpp
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * AST node for action signal.
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

