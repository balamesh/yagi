/**
 * @file   NodeQuantifiedFormula.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for quantified formulas
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
