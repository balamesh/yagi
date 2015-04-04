/**
 * @file   NodeOperatorIn.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for "tuple-in-set" formulas
 */

#include "NodeOperatorIn.h"

NodeOperatorIn::NodeOperatorIn() :
    tuple_(nullptr), setExpr_(nullptr)
{
}

NodeOperatorIn::~NodeOperatorIn()
{
}

