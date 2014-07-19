/*
 * NodeQuantifiedFormula.cpp
 *
 *  Created on: May 30, 2014
 *      Author: cmaier
 */

#include "NodeQuantifiedFormula.h"

NodeQuantifiedFormula::NodeQuantifiedFormula() :
    quantifier_(Quantifier::unknown), tuple_(nullptr), setExpr_(nullptr), suchFormula_(nullptr)
{
}

NodeQuantifiedFormula::~NodeQuantifiedFormula()
{
}

std::string NodeQuantifiedFormula::getQuantifierText()
{
  if (quantifier_ == Quantifier::all)
    return "for all";
  if (quantifier_ == Quantifier::exists)
    return "exists";

  throw new std::runtime_error("Unknown quantifier!");
}
