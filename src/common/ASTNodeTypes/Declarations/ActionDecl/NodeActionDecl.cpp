/**
 * @file   NodeActionDecl.cpp
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * AST node for action declarations.
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

