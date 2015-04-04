/**
 * @file   NodeWhileLoop.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for YAGI while-loops
 */

#include "NodeWhileLoop.h"

NodeWhileLoop::NodeWhileLoop() :
    formula_(nullptr), block_(nullptr)
{
}

NodeWhileLoop::~NodeWhileLoop()
{
}

