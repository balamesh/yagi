/*
 * VariableAssignment.h
 *
 *  Created on: May 26, 2014
 *      Author: cmaier
 */

#ifndef NODEVARIABLEASSIGNMENT_H_
#define NODEVARIABLEASSIGNMENT_H_

#include <memory>

#include "../ASTNodeBase.h"
#include "../Variables/NodeVariable.h"
#include "../Expressions/NodeValueExpression.h"

class NodeVariableAssignment: public ASTNodeBase
{
  private:
    std::shared_ptr<NodeVariable> variable_;
    std::shared_ptr<NodeValueExpression> valExpr_;

  public:
    NodeVariableAssignment();
    virtual ~NodeVariableAssignment();

    const std::shared_ptr<NodeValueExpression>& getValExpr() const
    {
      return valExpr_;
    }

    void setValExpr(const std::shared_ptr<NodeValueExpression>& valExpr)
    {
      valExpr_ = valExpr;
    }

    const std::shared_ptr<NodeVariable>& getVariable() const
    {
      return variable_;
    }

    void setVariable(const std::shared_ptr<NodeVariable>& variable)
    {
      variable_ = variable;
    }

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      visitor->visit(this);

      variable_->accept(visitor);
      valExpr_->accept(visitor);
    }
};

#endif /* NODEVARIABLEASSIGNMENT_H_ */
