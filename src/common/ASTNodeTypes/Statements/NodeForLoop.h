/*
 * NodeForLoop.h
 *
 *  Created on: Jun 5, 2014
 *      Author: cmaier
 */

#ifndef NODEFORLOOP_H_
#define NODEFORLOOP_H_

#include <memory>

#include "NodeStatementBase.h"
#include "NodeBlock.h"
#include "../Expressions/NodeSetExpression.h"
#include "../Tuple/NodeTuple.h"

class NodeForLoop: public NodeStatementBase
{
  private:
    std::shared_ptr<NodeTuple> tuple_;
    std::shared_ptr<NodeSetExpression> setExpr_;
    std::shared_ptr<NodeBlock> block_;

  public:
    NodeForLoop();
    virtual ~NodeForLoop();

    const std::shared_ptr<NodeBlock>& getBlock() const
    {
      return block_;
    }

    void setBlock(const std::shared_ptr<NodeBlock>& block)
    {
      block_ = block;
    }

    const std::shared_ptr<NodeSetExpression>& getSetExpr() const
    {
      return setExpr_;
    }

    void setSetExpr(const std::shared_ptr<NodeSetExpression>& setExpr)
    {
      setExpr_ = setExpr;
    }

    const std::shared_ptr<NodeTuple>& getTuple() const
    {
      return tuple_;
    }

    void setTuple(const std::shared_ptr<NodeTuple>& tuple)
    {
      tuple_ = tuple;
    }

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      tuple_->accept(visitor);
      setExpr_->accept(visitor);
      block_->accept(visitor);

      visitor->visit(this);
    }
};

#endif /* NODEFORLOOP_H_ */
