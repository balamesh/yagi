/*
 * NodeVariable.cpp
 *
 *  Created on: May 23, 2014
 *      Author: cmaier
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

