/**
 * @file   NodeExogenousEventDecl.cpp
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * AST node for exogenous event declaration.
 */

#include "NodeExogenousEventDecl.h"

NodeExogenousEventDecl::NodeExogenousEventDecl() :
    exoEventName_(nullptr), argList_(nullptr), block_(nullptr)
{

}

NodeExogenousEventDecl::~NodeExogenousEventDecl()
{

}

