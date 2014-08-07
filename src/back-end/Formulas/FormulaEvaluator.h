/*
 * FormulaEvaluator.h
 *
 *  Created on: Jul 17, 2014
 *      Author: cmaier
 */

#ifndef FORMULAEVALUATOR_H_
#define FORMULAEVALUATOR_H_

#include <string>
#include <vector>

#include "../../common/ASTNodeTypes/Formula/NodeAtomConnective.h"
#include "IFormulaEvaluator.h"

namespace yagi {
namespace database {
class DatabaseConnectorBase;
} /* namespace database */
} /* namespace yagi */

namespace yagi {
namespace execution {
class VariableTable;
} /* namespace execution */
} /* namespace yagi */

namespace yagi {
namespace formula {

class FormulaEvaluator: public IFormulaEvaluator
{
  private:
    bool performValueValueComparison(const std::string& lhs, const std::string& rhs,
        AtomConnective connective);

    bool performSetSetComparison(std::vector<std::vector<std::string>>& lhs,
        std::vector<std::vector<std::string>>& rhs, AtomConnective connective);

    yagi::execution::VariableTable* varTable_;
    yagi::database::DatabaseConnectorBase* db_;

  public:
    FormulaEvaluator(yagi::execution::VariableTable* varTable,
        yagi::database::DatabaseConnectorBase* db);
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
