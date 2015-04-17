/**
 * @file   IFormulaEvaluator.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Basic structure for evaluating YAGI formulas, more precisely logic sentences
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
