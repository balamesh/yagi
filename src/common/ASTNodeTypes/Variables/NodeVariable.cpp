/**
 * @file   NodeVariable.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for YAGI variables
 */

#include "NodeVariable.h"

NodeVariable::NodeVariable() :
    varName_("")
{
}

NodeVariable::NodeVariable(const std::string& varName) :
    varName_(varName)
{
}

NodeVariable::~NodeVariable()
{
}

