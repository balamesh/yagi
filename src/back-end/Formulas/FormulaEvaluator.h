/**
 * @file   FormulaEvaluator.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Responsible for evaluating YAGI formulas, more precisely logic sentences
 */

/*
 This file is part of YAGI.

 YAGI is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3.0 of the License, or (at your option) any later version.

 YAGI is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with YAGI.
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

/**
 * Responsible for evaluating YAGI formulas, more precisely logic sentences
 */
class FormulaEvaluator: public IFormulaEvaluator
{
  private:

    /**
     * Compares two YAGI vaues
     * @param lhs Left-hand side value
     * @param rhs Right-hand side value
     * @param connective Comparison connective
     * @return True if comparison holds, false otherwise
     */
    bool performValueValueComparison(const std::string& lhs, const std::string& rhs,
        AtomConnective connective);

    /**
     * Compares two YAGI sets
     * @param lhs Left-hand side set
     * @param rhs Right-hand side set
     * @param connective Comparison connective
     * @return True if comparison holds, false otherwise
     */
    bool performSetSetComparison(std::vector<std::vector<std::string>>& lhs,
        std::vector<std::vector<std::string>>& rhs, AtomConnective connective);

    /**
     * Variable table to use for formula evaluation
     */
    yagi::execution::VariableTable* varTable_;

    /**
     * Database to use for formula evaluation
     */
    yagi::database::DatabaseConnectorBase* db_;

  public:

    /**
     * Ctor
     * @param varTable Variable table to use for formula evaluation
     * @param db Database instance to use for formula evaluation
     */
    FormulaEvaluator(yagi::execution::VariableTable* varTable,
        yagi::database::DatabaseConnectorBase* db);

    /**
     * Default dtor
     */
    virtual ~FormulaEvaluator();

    /**
     * Evaluate a logical constant, i.e. true or false
     * @param constant The constant node
     * @return True if it holds, false otherwise
     */
    virtual bool evaluateConstant(NodeConstant* constant) override;

    /**
     * Evaluate a logical atom
     * @param atom The atom node
     * @return True if it holds, false otherwise
     */
    virtual bool evaluateAtom(NodeAtom* atom) override;

    /**
     * Evaluate formula negation
     * @param negation The negation node
     * @return True if it holds, false otherwise
     */
    virtual bool evaluateNegation(NodeNegation* negation) override;

    /**
     * Evaluate compound formula
     * @param compoundFormula The compound formula node
     * @return True if it holds, false otherwise
     */
    virtual bool evaluateCompoundFormula(NodeCompoundFormula* compoundFormula) override;

    /**
     * Evaluate quantified (exists, all) formula
     * @param quantifiedFormula The quantified formula node
     * @return True if it holds, false otherwise
     */
    virtual bool evaluateQuantifiedFormula(NodeQuantifiedFormula* quantifiedFormula) override;

    /**
     * Evaluate 'tuple in set' formula
     * @param inFormula The formula node
     * @return True if it holds, false otherwise
     */
    virtual bool evaluateInFormula(NodeOperatorIn* inFormula) override;
};

} /* namespace formula */
} /* namespace yagi */

#endif /* FORMULAEVALUATOR_H_ */
