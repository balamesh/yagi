/*
 * IFormulaEvaluator.cpp
 *
 *  Created on: Jul 17, 2014
 *      Author: cmaier
 */

#include "IFormulaEvaluator.h"

namespace yagi {
namespace formula {

IFormulaEvaluator::IFormulaEvaluator() :
    printFormulaEvaluationResults_(true), ctx_(nullptr)
{
}

IFormulaEvaluator::IFormulaEvaluator(ASTNodeVisitorBase* ctx) :
    printFormulaEvaluationResults_(true), ctx_(ctx)
{
}

IFormulaEvaluator::~IFormulaEvaluator()
{
}

} /* namespace formula */
} /* namespace yagi */
