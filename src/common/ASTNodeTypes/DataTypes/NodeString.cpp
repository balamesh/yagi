/**
 * @file   NodeString.cpp
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * AST node for string elements.
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

