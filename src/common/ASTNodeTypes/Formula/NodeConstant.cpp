/*
 * NodeConstant.cpp
 *
 *  Created on: May 28, 2014
 *      Author: cmaier
 */

#include "NodeConstant.h"

NodeConstant::NodeConstant() :
    truthValue_(false)
{
}

NodeConstant::~NodeConstant()
{
}

void NodeConstant::fromString(const std::string& truthVal)
{
  if (truthVal == "true")
    truthValue_ = true;
  else if (truthVal == "false")
    truthValue_ = false;
  else
    throw std::runtime_error("Invalid atom connective string '" + truthVal + "'!");
}

