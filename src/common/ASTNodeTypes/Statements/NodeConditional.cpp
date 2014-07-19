/*
 * NodeConditional.cpp
 *
 *  Created on: Jun 5, 2014
 *      Author: cmaier
 */

#include "NodeConditional.h"

NodeConditional::NodeConditional() :
    formula_(nullptr), ifBlock_(nullptr), elseBlock_(nullptr)
{
}

NodeConditional::~NodeConditional()
{
}

