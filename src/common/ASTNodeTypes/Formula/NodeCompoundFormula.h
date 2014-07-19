/*
 * NodeCompoundFormula.h
 *
 *  Created on: May 30, 2014
 *      Author: cmaier
 */

#ifndef NODECOMPOUNDFORMULA_H_
#define NODECOMPOUNDFORMULA_H_

#include <memory>

#include "NodeFormulaBase.h"
#include "NodeAtom.h"
#include "NodeFormulaConnective.h"

class NodeCompoundFormula: public NodeFormulaBase
{
  private:
    std::shared_ptr<NodeFormulaBase> leftOperand_;
    std::shared_ptr<NodeFormulaConnective> connective_;
    std::shared_ptr<NodeFormulaBase> rightOperand_;

  public:
    DEFINE_VISITABLE()
    NodeCompoundFormula();
    virtual ~NodeCompoundFormula();

    const std::shared_ptr<NodeFormulaConnective>& getConnective() const
    {
      return connective_;
    }

    void setConnective(const std::shared_ptr<NodeFormulaConnective>& connective)
    {
      connective_ = connective;
    }

    const std::shared_ptr<NodeFormulaBase>& getLeftOperand() const
    {
      return leftOperand_;
    }

    void setLeftOperand(const std::shared_ptr<NodeFormulaBase>& leftOperand)
    {
      leftOperand_ = leftOperand;
    }

    const std::shared_ptr<NodeFormulaBase>& getRightOperand() const
    {
      return rightOperand_;
    }

    void setRightOperand(const std::shared_ptr<NodeFormulaBase>& rightOperand)
    {
      rightOperand_ = rightOperand;
    }
};

#endif /* NODECOMPOUNDFORMULA_H_ */
