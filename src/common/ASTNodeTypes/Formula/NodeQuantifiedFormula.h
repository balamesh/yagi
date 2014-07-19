/*
 * NodeQuantifiedFormula.h
 *
 *  Created on: May 30, 2014
 *      Author: cmaier
 */

#ifndef NODEQUANTIFIEDFORMULA_H_
#define NODEQUANTIFIEDFORMULA_H_

#include <memory>

#include "NodeFormulaBase.h"
#include "../Tuple/NodeTuple.h"
#include "../Expressions/NodeSetExpression.h"

enum class Quantifier
{
  exists, all, unknown
};

class NodeQuantifiedFormula: public NodeFormulaBase
{
  private:

    Quantifier quantifier_;
    std::shared_ptr<NodeTuple> tuple_;
    std::shared_ptr<NodeSetExpression> setExpr_;
    std::shared_ptr<NodeFormulaBase> suchFormula_;

  public:
    DEFINE_VISITABLE()
    NodeQuantifiedFormula();
    virtual ~NodeQuantifiedFormula();

    std::string getQuantifierText();

    const std::shared_ptr<NodeFormulaBase>& getSuchFormula() const
    {
      return suchFormula_;
    }

    void setSuchFormula(const std::shared_ptr<NodeFormulaBase>& formula)
    {
      suchFormula_ = formula;
    }

    Quantifier getQuantifier() const
    {
      return quantifier_;
    }

    void setQuantifier(Quantifier quantifier)
    {
      quantifier_ = quantifier;
    }

    const std::shared_ptr<NodeTuple>& getTuple() const
    {
      return tuple_;
    }

    void setTuple(const std::shared_ptr<NodeTuple>& tuple)
    {
      tuple_ = tuple;
    }

    const std::shared_ptr<NodeSetExpression>& getSetExpr() const
    {
      return setExpr_;
    }

    void setSetExpr(const std::shared_ptr<NodeSetExpression>& setExpr)
    {
      setExpr_ = setExpr;
    }
};

#endif /* NODEQUANTIFIEDFORMULA_H_ */
