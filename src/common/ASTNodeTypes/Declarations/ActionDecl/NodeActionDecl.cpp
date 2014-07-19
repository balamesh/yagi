/*
 * NodeActionDecl.cpp
 *
 *  Created on: May 23, 2014
 *      Author: cmaier
 */

#include "NodeActionDecl.h"

NodeActionDecl::NodeActionDecl() :
    actionName_(nullptr), varList_(nullptr), settingVarList_(nullptr), actionPrecondition_(nullptr), actionEffect_(
        nullptr), signal_(nullptr)
{
}

NodeActionDecl::~NodeActionDecl()
{
}

