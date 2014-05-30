/*
 * NodeOperatorIn.h
 *
 *  Created on: May 30, 2014
 *      Author: cmaier
 */

#ifndef NODEOPERATORIN_H_
#define NODEOPERATORIN_H_

#include <memory>

#include "../Tuple/NodeTuple.h"
#include "../Expressions/NodeSetExpression.h"

#include "NodeFormulaBase.h"

class NodeOperatorIn: public NodeFormulaBase
{
  private:
    std::shared_ptr<NodeTuple> tuple_;
    std::shared_ptr<NodeSetExpression> setExpr_;

  public:
    NodeOperatorIn();
    virtual ~NodeOperatorIn();

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
      //TODO: implement this
      //visitor->visit(this);
    }
};

#endif /* NODEOPERATORIN_H_ */
