/**
 * @file   NodeConditional.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for a YAGI conditional
 */

#include "NodeConditional.h"

NodeConditional::NodeConditional() :
    formula_(nullptr), ifBlock_(nullptr), elseBlock_(nullptr)
{
}

NodeConditional::~NodeConditional()
{
}

