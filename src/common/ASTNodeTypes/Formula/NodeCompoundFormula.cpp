/**
 * @file   NodeCompoundFormula.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for compound formulas
 */

#include "NodeCompoundFormula.h"

NodeCompoundFormula::NodeCompoundFormula() :
    leftOperand_(nullptr), connective_(nullptr), rightOperand_(nullptr)
{
}

NodeCompoundFormula::~NodeCompoundFormula()
{

}

