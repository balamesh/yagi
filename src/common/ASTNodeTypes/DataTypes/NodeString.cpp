/*
 * NodeString.cpp
 *
 *  Created on: May 22, 2014
 *      Author: cmaier
 */

#include "NodeString.h"

NodeString::NodeString() :
    string_("")
{
}

NodeString::NodeString(const std::string& str) :
    string_(str)
{
}

NodeString::~NodeString()
{
}

