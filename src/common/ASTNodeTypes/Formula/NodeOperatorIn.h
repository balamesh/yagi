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
    std::shared_ptr<ASTNodeBase<>> setExpr_;

  public:
    DEFINE_VISITABLE()
    NodeOperatorIn();
    virtual ~NodeOperatorIn();

    const std::shared_ptr<ASTNodeBase<>>& getSetExpr() const
    {
      return setExpr_;
    }

    void setSetExpr(const std::shared_ptr<ASTNodeBase<>>& setExpr)
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
};

#endif /* NODEOPERATORIN_H_ */
