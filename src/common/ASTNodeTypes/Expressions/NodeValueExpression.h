/**
 * @file   NodeValueExpression.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for value expressions
 */

/*
 This file is part of YAGI.

 YAGI is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3.0 of the License, or (at your option) any later version.

 YAGI is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with YAGI.
*/


#ifndef NODEVALUEEXPRESSION_H_
#define NODEVALUEEXPRESSION_H_

#include "../ASTNodeBase.h"
#include "../DataTypes/NodeString.h"
#include "../Variables/NodeVariable.h"
#include "NodeExpressionOperator.h"

#include <memory>

/**
 * AST node class for value expressions
 */
class NodeValueExpression: public ASTNodeBase<>
{
  private:
    /**
     * Value expression operator
     */
    std::shared_ptr<NodeExpressionOperator> operator_;

    /**
     * Left-hand side of the expression
     */
    std::shared_ptr<ASTNodeBase<>> lhs_;

    /**
     * Right-hand side of the expression
     */
    std::shared_ptr<ASTNodeBase<>> rhs_;
  public:
    DEFINE_VISITABLE()
    /**
     * Default ctor
     */
    NodeValueExpression();

    /**
     * Default dtor
     */
    virtual ~NodeValueExpression();

    /**
     * Checks whether or not the passed value is a valid
     * @param valueToAssign The value to check
     * @return True if valid, false otherwise
     */
    static bool isPassedTypeValid(const std::shared_ptr<ASTNodeBase<>>& valueToAssign);

    /**
     * Getter for the lhs of the expression
     * @return The lhs of the expression
     */
    const std::shared_ptr<ASTNodeBase<>>& getLhs() const
    {
      return lhs_;
    }

    /**
     * Setter for the lhs of the expression
     * @param lhs The lhs of the expression
     */
    void setLhs(const std::shared_ptr<ASTNodeBase<>>& lhs)
    {
      if (isPassedTypeValid(lhs))
        this->lhs_ = lhs;
      else
        throw std::runtime_error("Invalid Type passed to ValueExpression (lhs)!");
    }

    /**
     * Getter for the rhs of the expression
     * @return The rhs of the expression
     */
    const std::shared_ptr<ASTNodeBase<>>& getRhs() const
    {
      return rhs_;
    }

    /**
     * Setter for the rhs of the expression
     * @param rhs The rhs of the expression
     */
    void setRhs(const std::shared_ptr<ASTNodeBase<>>& rhs)
    {
      if (isPassedTypeValid(rhs))
        this->rhs_ = rhs;
      else
        throw std::runtime_error("Invalid Type passed to ValueExpression (rhs)!");
    }

    /**
     * Getter for the expression operator
     * @return The expression operator
     */
    const std::shared_ptr<NodeExpressionOperator>& getOperator() const
    {
      return operator_;
    }

    /**
     * Setter for the expression operator
     * @param _operator The expression operator
     */
    void setOperator(const std::shared_ptr<NodeExpressionOperator>& _operator)
    {
      operator_ = _operator;
    }
};

#endif /* NODEVALUEEXPRESSION_H_ */
