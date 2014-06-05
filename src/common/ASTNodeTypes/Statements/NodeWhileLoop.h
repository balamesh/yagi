/*
 * NodeWhileLoop.h
 *
 *  Created on: Jun 5, 2014
 *      Author: cmaier
 */

#ifndef NODEWHILELOOP_H_
#define NODEWHILELOOP_H_

#include "NodeStatementBase.h"

#include "../Formula/NodeFormulaBase.h"
#include "NodeBlock.h"

class NodeWhileLoop: public NodeStatementBase
{
  private:
    std::shared_ptr<NodeFormulaBase> formula_;
    std::shared_ptr<NodeBlock> block_;

  public:
    NodeWhileLoop();
    virtual ~NodeWhileLoop();

    const std::shared_ptr<NodeBlock>& getBlock() const
    {
      return block_;
    }

    void setBlock(const std::shared_ptr<NodeBlock>& block)
    {
      block_ = block;
    }

    const std::shared_ptr<NodeFormulaBase>& getFormula() const
    {
      return formula_;
    }

    void setFormula(const std::shared_ptr<NodeFormulaBase>& formula)
    {
      formula_ = formula;
    }

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      //TODO: implement this
      //visitor->visit(this);
    }
};

#endif /* NODEWHILELOOP_H_ */
