/*
 * ValueExpression.h
 *
 *  Created on: May 26, 2014
 *      Author: cmaier
 */

#ifndef NODEVALUEEXPRESSION_H_
#define NODEVALUEEXPRESSION_H_

#include "../ASTNodeBase.h"
#include "../DataTypes/NodeInteger.h"
#include "../DataTypes/NodeString.h"
#include "../Variables/NodeVariable.h"
#include "NodeValueExpressionOperator.h"

#include <memory>

class NodeValueExpression: public ASTNodeBase
{
  private:
    std::shared_ptr<NodeValueExpressionOperator> operator_;
    std::shared_ptr<ASTNodeBase> lhs_;
    std::shared_ptr<ASTNodeBase> rhs_;

    bool IsPassedTypeValid(const std::shared_ptr<ASTNodeBase>& valueToAssign);
  public:
    NodeValueExpression();
    virtual ~NodeValueExpression();

    const std::shared_ptr<ASTNodeBase>& getLhs() const
    {
      return lhs_;
    }

    void setLhs(const std::shared_ptr<ASTNodeBase>& lhs)
    {
      if (IsPassedTypeValid(lhs))
        this->lhs_ = lhs;
      else
        throw std::runtime_error(
            "Invalid Type passed to ValueExpression (lhs)!");
    }

    const std::shared_ptr<ASTNodeBase>& getRhs() const
    {
      return rhs_;
    }

    void setRhs(const std::shared_ptr<ASTNodeBase>& rhs)
    {
      if (IsPassedTypeValid(rhs))
        this->rhs_ = rhs;
      else
        throw std::runtime_error(
            "Invalid Type passed to ValueExpression (rhs)!");
    }

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      visitor->visit(this);

      if (operator_ != nullptr) operator_->accept(visitor);
      if (lhs_ != nullptr) lhs_->accept(visitor);
      rhs_->accept(visitor); //can't be null!
    }

    const std::shared_ptr<NodeValueExpressionOperator>& getOperator() const
    {
      return operator_;
    }

    void setOperator(
        const std::shared_ptr<NodeValueExpressionOperator>& _operator)
    {
      operator_ = _operator;
    }
};

#endif /* NODEVALUEEXPRESSION_H_ */
