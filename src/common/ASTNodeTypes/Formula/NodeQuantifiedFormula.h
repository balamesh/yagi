/**
 * @file   NodeQuantifiedFormula.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for quantified formulas
 */

#ifndef NODEQUANTIFIEDFORMULA_H_
#define NODEQUANTIFIEDFORMULA_H_

#include <memory>

#include "NodeFormulaBase.h"
#include "../Tuple/NodeTuple.h"
#include "../Expressions/NodeSetExpression.h"

/**
 * First-order quantifiers
 */
enum class Quantifier
{
  exists, all, unknown
};

/**
 * AST node class for quantified formulas
 */
class NodeQuantifiedFormula: public NodeFormulaBase
{
  private:
    /**
     * The quantifier
     */
    Quantifier quantifier_;

    /**
     * The tuple to check
     */
    std::shared_ptr<NodeTuple> tuple_;

    /**
     * The set to check
     */
    std::shared_ptr<NodeSetExpression> setExpr_;

    /**
     * Formula to be evaluated
     */
    std::shared_ptr<NodeFormulaBase> suchFormula_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeQuantifiedFormula();

    /**
     * Default dtor
     */
    virtual ~NodeQuantifiedFormula();

    /**
     * Stringifies the quantifier
     * @return The stringified quantifier
     */
    std::string getQuantifierText();

    /**
     * Getter for the formula to be evaluated
     * @return The formula to be evaluated
     */
    const std::shared_ptr<NodeFormulaBase>& getSuchFormula() const
    {
      return suchFormula_;
    }

    /**
     * Setter for the formula to be evaluated
     * @param formula The formula to be evaluated
     */
    void setSuchFormula(const std::shared_ptr<NodeFormulaBase>& formula)
    {
      suchFormula_ = formula;
    }

    /**
     * Getter for the quantifier
     * @return The quantifier
     */
    Quantifier getQuantifier() const
    {
      return quantifier_;
    }

    /**
     * Setter for the quantifier
     * @param quantifier The quantifier
     */
    void setQuantifier(Quantifier quantifier)
    {
      quantifier_ = quantifier;
    }

    /**
     * Getter for the tuple
     * @return The tuple
     */
    const std::shared_ptr<NodeTuple>& getTuple() const
    {
      return tuple_;
    }

    /**
     * Setter for the tuple
     * @param tuple The tuple
     */
    void setTuple(const std::shared_ptr<NodeTuple>& tuple)
    {
      tuple_ = tuple;
    }

    /**
     * Getter for the set
     * @return The set
     */
    const std::shared_ptr<NodeSetExpression>& getSetExpr() const
    {
      return setExpr_;
    }

    /**
     * Setter for the set
     * @param setExpr The set
     */
    void setSetExpr(const std::shared_ptr<NodeSetExpression>& setExpr)
    {
      setExpr_ = setExpr;
    }
};

#endif /* NODEQUANTIFIEDFORMULA_H_ */
