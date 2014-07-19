/*
 * NodeProcDecl.cpp
 *
 *  Created on: Jun 4, 2014
 *      Author: cmaier
 */

#include "NodeProcDecl.h"

NodeProcDecl::NodeProcDecl() :
    procName_(nullptr), argList_(nullptr), block_(nullptr)
{
}

NodeProcDecl::~NodeProcDecl()
{
}

