/*
 * NodeCompoundFormula.cpp
 *
 *  Created on: May 30, 2014
 *      Author: cmaier
 */

#include "NodeCompoundFormula.h"

NodeCompoundFormula::NodeCompoundFormula() :
    leftOperand_(nullptr), connective_(nullptr), rightOperand_(nullptr)
{
}

NodeCompoundFormula::~NodeCompoundFormula()
{

}

