/*
 * NodeFormula.cpp
 *
 *  Created on: May 23, 2014
 *      Author: cmaier
 */

#include "NodeAtom.h"

NodeAtom::NodeAtom() :
    leftOperand_(nullptr), connective_(nullptr), rightOperand_(nullptr)
{
}

NodeAtom::~NodeAtom()
{
}

