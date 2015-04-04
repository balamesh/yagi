/**
 * @file   NodePick.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for a YAGI pick-statement
 */

#include "NodePick.h"

NodePick::NodePick() :
    tuple_(nullptr), setExpr_(nullptr), block_(nullptr)
{
}

NodePick::~NodePick()
{
}

