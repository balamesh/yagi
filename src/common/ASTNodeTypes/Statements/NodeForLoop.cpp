/**
 * @file   NodeForLoop.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for a YAGI for-loop
 */

#include "NodeForLoop.h"

NodeForLoop::NodeForLoop() :
    tuple_(nullptr), setExpr_(nullptr), block_(nullptr)
{
}

NodeForLoop::~NodeForLoop()
{
}

