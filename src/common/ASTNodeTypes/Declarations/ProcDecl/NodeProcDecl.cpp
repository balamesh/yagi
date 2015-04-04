/**
 * @file   NodeProcDecl.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for procedure declarations.
 */

#include "NodeProcDecl.h"

NodeProcDecl::NodeProcDecl() :
    procName_(nullptr), argList_(nullptr), block_(nullptr)
{
}

NodeProcDecl::~NodeProcDecl()
{
}

