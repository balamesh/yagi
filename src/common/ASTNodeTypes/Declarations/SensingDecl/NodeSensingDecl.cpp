/**
 * @file   NodeSensingDecl.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for sensing declarations.
 */

#include "NodeSensingDecl.h"

NodeSensingDecl::NodeSensingDecl() :
    sensingName_(nullptr), varList_(nullptr), settingVarList_(nullptr), formula_(nullptr)
{
}

NodeSensingDecl::~NodeSensingDecl()
{
}

