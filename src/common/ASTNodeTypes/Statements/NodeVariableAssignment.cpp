/**
 * @file   NodeVariableAssignment.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for YAGI assignments to variables
 */

#include "NodeVariableAssignment.h"

NodeVariableAssignment::NodeVariableAssignment() :
    variable_(nullptr), value_(nullptr)
{
}

NodeVariableAssignment::~NodeVariableAssignment()
{
}

