/*
 * NodeFluentAssignment.h
 *
 *  Created on: May 27, 2014
 *      Author: cmaier
 */

#ifndef NODEFLUENTASSIGNMENT_H_
#define NODEFLUENTASSIGNMENT_H_

#include "../../ASTNodeTypes/Identifier/NodeID.h"
#include "../../ASTNodeTypes/Expressions/NodeSetExpression.h"
#include "../../ASTNodeTypes/Expressions/NodeSetExpressionOperator.h"
#include "NodeStatementBase.h"

#include <memory>

class NodeFluentAssignment: public NodeStatementBase
{
  private:
    std::shared_ptr<NodeID> fluentName_;
    std::shared_ptr<NodeSetExpressionOperator> operator_;
    std::shared_ptr<NodeSetExpression> setExpr_;

  public:
    DEFINE_VISITABLE()
    NodeFluentAssignment();
    virtual ~NodeFluentAssignment();

    const std::shared_ptr<NodeID>& getFluentName() const
    {
      return fluentName_;
    }

    void setFluentName(const std::shared_ptr<NodeID>& fluentName)
    {
      fluentName_ = fluentName;
    }

    const std::shared_ptr<NodeSetExpressionOperator>& getOperator() const
    {
      return operator_;
    }

    void setOperator(const std::shared_ptr<NodeSetExpressionOperator>& _operator)
    {
      operator_ = _operator;
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

#endif /* NODEFLUENTASSIGNMENT_H_ */
