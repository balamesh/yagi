/**
 * @file   NodeIDAssignment.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for a YAGI assignment
 */

#include "NodeIDAssignment.h"

NodeIDAssignment::NodeIDAssignment() :
    fluentName_(nullptr), operator_(nullptr), setExpr_(nullptr)
{
}

NodeIDAssignment::~NodeIDAssignment()
{
}

