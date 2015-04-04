/**
 * @file   NodeAtom.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for atoms
 */

#include "NodeAtom.h"

NodeAtom::NodeAtom() :
    leftOperand_(nullptr), connective_(nullptr), rightOperand_(nullptr)
{
}

NodeAtom::~NodeAtom()
{
}

