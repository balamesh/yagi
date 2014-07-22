/*
 * FormulaEvaluator.cpp
 *
 *  Created on: Jul 17, 2014
 *      Author: cmaier
 */

#include "FormulaEvaluator.h"

namespace yagi {
namespace formula {

FormulaEvaluator::FormulaEvaluator()
{
  // TODO Auto-generated constructor stub

}

FormulaEvaluator::~FormulaEvaluator()
{
  // TODO Auto-generated destructor stub
}

bool FormulaEvaluator::evaluateConstant(NodeConstant* constant)
{
  auto ret = constant->getTruthValue();

  if (printFormulaEvaluationResults_)
    std::cout << "Constant = " << (ret ? "true" : "false") << std::endl;

  return ret;
}

bool FormulaEvaluator::evaluateAtom(NodeAtom* atom)
{
  return true;
}

} /* namespace formula */
} /* namespace yagi */
