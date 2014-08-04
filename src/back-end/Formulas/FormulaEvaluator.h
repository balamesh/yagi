/*
 * FormulaEvaluator.h
 *
 *  Created on: Jul 17, 2014
 *      Author: cmaier
 */

#ifndef FORMULAEVALUATOR_H_
#define FORMULAEVALUATOR_H_

#include <iostream>

#include "IFormulaEvaluator.h"
#include "../TreeHelper.h"
#include "../../common/ASTNodeTypes/Expressions/NodeSetExpression.h"
#include "../../utils/ToStringHelper.h"
#include "../../utils/CustomComparers.h"
#include "../Variables/VariableTableManager.h"
#include "../Database/DatabaseManager.h"
#include "../SQLGenerator.h"

using namespace yagi::execution;
using namespace yagi::database;

namespace yagi {
namespace formula {

class FormulaEvaluator: public IFormulaEvaluator
{
  private:
    bool performValueValueComparison(const std::string& lhs, const std::string& rhs,
        AtomConnective connective);

    bool performSetSetComparison(std::vector<std::vector<std::string>>& lhs,
        std::vector<std::vector<std::string>>& rhs, AtomConnective connective);

  public:
    FormulaEvaluator();
    virtual ~FormulaEvaluator();

    virtual bool evaluateConstant(NodeConstant* constant) override;
    virtual bool evaluateAtom(NodeAtom* atom) override;
    virtual bool evaluateNegation(NodeNegation* negation) override;
    virtual bool evaluateCompoundFormula(NodeCompoundFormula* compoundFormula) override;
    virtual bool evaluateQuantifiedFormula(NodeQuantifiedFormula* quantifiedFormula) override;
    virtual bool evaluateInFormula(NodeOperatorIn* inFormula) override;
};

} /* namespace formula */
} /* namespace yagi */

#endif /* FORMULAEVALUATOR_H_ */
