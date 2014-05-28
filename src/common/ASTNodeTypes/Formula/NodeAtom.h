/*
 * NodeFormula.h
 *
 *  Created on: May 23, 2014
 *      Author: cmaier
 */

#ifndef NODEATOM_H_
#define NODEATOM_H_

#include <memory>

#include "NodeFormulaBase.h"
#include "NodeConnective.h"

class NodeAtom: public NodeFormulaBase
{
  private:
    std::shared_ptr<ASTNodeBase> leftOperand_;
    std::shared_ptr<NodeConnective> connective_;
    std::shared_ptr<ASTNodeBase> rightOperand_;

  public:
    NodeAtom();
    virtual ~NodeAtom();

    const std::shared_ptr<NodeConnective>& getConnective() const
    {
      return connective_;
    }

    void setConnective(const std::shared_ptr<NodeConnective>& connective)
    {
      connective_ = connective;
    }

    const std::shared_ptr<ASTNodeBase>& getLeftOperand() const
    {
      return leftOperand_;
    }

    void setLeftOperand(const std::shared_ptr<ASTNodeBase>& leftOperand)
    {
      leftOperand_ = leftOperand;
    }

    const std::shared_ptr<ASTNodeBase>& getRightOperand() const
    {
      return rightOperand_;
    }

    void setRightOperand(const std::shared_ptr<ASTNodeBase>& rightOperand)
    {
      rightOperand_ = rightOperand;
    }

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      //TODO: implement this
      //visitor->visit(this);
    }
};

#endif /* NODEATOM_H_ */
