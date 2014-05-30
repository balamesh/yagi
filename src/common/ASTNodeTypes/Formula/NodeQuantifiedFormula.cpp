/*
 * NodeQuantifiedFormula.cpp
 *
 *  Created on: May 30, 2014
 *      Author: cmaier
 */

#include "NodeQuantifiedFormula.h"

NodeQuantifiedFormula::NodeQuantifiedFormula()
{
  // TODO Auto-generated constructor stub
  quantifier_ = Quantifier::unknown;
  setExpr_ = nullptr;
  tuple_ = nullptr;
  formula_ = nullptr;

}

NodeQuantifiedFormula::~NodeQuantifiedFormula()
{
  // TODO Auto-generated destructor stub
}

