/**
 * @file   IFormulaEvaluator.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Basic structure for evaluating YAGI formulas, more precisely logic sentences
 */

#ifndef IFORMULAEVALUATOR_H_
#define IFORMULAEVALUATOR_H_

#include "../../common/ASTNodeTypes/Formula/NodeConstant.h"
#include "../../common/ASTNodeTypes/Formula/NodeAtom.h"
#include "../../common/ASTNodeTypes/Formula/NodeNegation.h"
#include "../../common/ASTNodeTypes/Formula/NodeCompoundFormula.h"
#include "../../common/ASTNodeTypes/Formula/NodeQuantifiedFormula.h"
#include "../../common/ASTNodeTypes/Formula/NodeOperatorIn.h"
#include <memory>

namespace yagi {
namespace formula {

/**
 * Abstract class for evaluating YAGI formulas, more precisely logic sentences
 */
class IFormulaEvaluator
{
  protected:

    /**
     * If true, print evaluation results of (sub)-formulas for debugging
     */
    bool printFormulaEvaluationResults_;

    /**
     * Current context
     */
    ASTNodeVisitorBase* ctx_;

  public:

    /**
     * Default ctor
     */
    IFormulaEvaluator();

    /**
     * Ctor
     * @param ctx Context to use
     */
    IFormulaEvaluator(ASTNodeVisitorBase* ctx);

    /**
     * Default dtor
     */
    virtual ~IFormulaEvaluator();

    /**
     * Setter for current context
     * @param ctx The context to use
     */
    void setContext(ASTNodeVisitorBase* ctx)
    {
      ctx_ = ctx;
    }

    /**
     * Evaluate a logical constant, i.e. true or false
     * @param constant The constant node
     * @return True if it holds, false otherwise
     */
    virtual bool evaluateConstant(NodeConstant* constant) = 0;

    /**
     * Evaluate a logical atom
     * @param atom The atom node
     * @return True if it holds, false otherwise
     */
    virtual bool evaluateAtom(NodeAtom* atom) = 0;

    /**
     * Evaluate formula negation
     * @param negation The negation node
     * @return True if it holds, false otherwise
     */
    virtual bool evaluateNegation(NodeNegation* negation) = 0;

    /**
     * Evaluate compound formula
     * @param compoundFormula The compound formula node
     * @return True if it holds, false otherwise
     */
    virtual bool evaluateCompoundFormula(NodeCompoundFormula* compoundFormula) = 0;

    /**
     * Evaluate quantified (exists, all) formula
     * @param quantifiedFormula The quantified formula node
     * @return True if it holds, false otherwise
     */
    virtual bool evaluateQuantifiedFormula(NodeQuantifiedFormula* quantifiedFormula) = 0;

    /**
     * Evaluate 'tuple in set' formula
     * @param inFormula The formula node
     * @return True if it holds, false otherwise
     */
    virtual bool evaluateInFormula(NodeOperatorIn* inFormula) = 0;
};

} /* namespace formula */
} /* namespace yagi */

#endif /* IFORMULAEVALUATOR_H_ */
