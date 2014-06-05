/*
 * NodeConditional.h
 *
 *  Created on: Jun 5, 2014
 *      Author: cmaier
 */

#ifndef NODECONDITIONAL_H_
#define NODECONDITIONAL_H_

#include <memory>

#include "NodeStatementBase.h"
#include "../Formula/NodeFormulaBase.h"
#include "NodeBlock.h"

class NodeConditional: public NodeStatementBase
{
  private:
    std::shared_ptr<NodeFormulaBase> formula_;
    std::shared_ptr<NodeBlock> ifBlock_;
    std::shared_ptr<NodeBlock> elseBlock_;

  public:
    NodeConditional();
    virtual ~NodeConditional();

    const std::shared_ptr<NodeBlock>& getElseBlock() const
    {
      return elseBlock_;
    }

    void setElseBlock(const std::shared_ptr<NodeBlock>& elseBlock)
    {
      elseBlock_ = elseBlock;
    }

    const std::shared_ptr<NodeFormulaBase>& getFormula() const
    {
      return formula_;
    }

    void setFormula(const std::shared_ptr<NodeFormulaBase>& formula)
    {
      formula_ = formula;
    }

    const std::shared_ptr<NodeBlock>& getIfBlock() const
    {
      return ifBlock_;
    }

    void setIfBlock(const std::shared_ptr<NodeBlock>& ifBlock)
    {
      ifBlock_ = ifBlock;
    }

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      formula_->accept(visitor);
      ifBlock_->accept(visitor);
      if (elseBlock_ != nullptr) elseBlock_->accept(visitor);

      visitor->visit(this);
    }
};

#endif /* NODECONDITIONAL_H_ */
