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
#include "NodeAtomConnective.h"

class NodeAtom: public NodeFormulaBase
{
  private:
    std::shared_ptr<ASTNodeBase<>> leftOperand_;
    std::shared_ptr<NodeAtomConnective> connective_;
    std::shared_ptr<ASTNodeBase<>> rightOperand_;

  public:
    DEFINE_VISITABLE()
    NodeAtom();
    virtual ~NodeAtom();

    const std::shared_ptr<NodeAtomConnective>& getConnective() const
    {
      return connective_;
    }

    void setConnective(const std::shared_ptr<NodeAtomConnective>& connective)
    {
      connective_ = connective;
    }

    const std::shared_ptr<ASTNodeBase<>>& getLeftOperand() const
    {
      return leftOperand_;
    }

    void setLeftOperand(const std::shared_ptr<ASTNodeBase<>>& leftOperand)
    {
      leftOperand_ = leftOperand;
    }

    const std::shared_ptr<ASTNodeBase<>>& getRightOperand() const
    {
      return rightOperand_;
    }

    void setRightOperand(const std::shared_ptr<ASTNodeBase<>>& rightOperand)
    {
      rightOperand_ = rightOperand;
    }

//    virtual void accept(ASTNodeVisitorBase* visitor) override
//    {
//      visitor->visit(this);
//
//      leftOperand_->accept(visitor);
//      connective_->accept(visitor);
//      rightOperand_->accept(visitor);
//    }
};

#endif /* NODEATOM_H_ */
