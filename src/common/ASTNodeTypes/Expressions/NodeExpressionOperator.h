/**
 * @file   NodeExpressionOperator.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for the expression operator
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


#ifndef NODEEXPRESSIONOPERATOR_H_
#define NODEEXPRESSIONOPERATOR_H_

#include <string>
#include <stdexcept>

#include "../ASTNodeBase.h"

/**
 * Possible expression operators
 */
enum class ExprOperator
{
  Plus, Minus, Unknown
};

/**
 * AST node class for the expression operator
 */
class NodeExpressionOperator: public ASTNodeBase<>
{
  private:
    /**
     * The expression operator
     */
    ExprOperator operator_;

  public:
    DEFINE_VISITABLE()
    /**
     * Default ctor
     */
    NodeExpressionOperator();

    /**
     * Default dtor
     */
    virtual ~NodeExpressionOperator();

    /**
     * Getter for the expression operator
     * @return The expression operator
     */
    ExprOperator getOperator() const
    {
      return operator_;
    }

    /**
     * Setter for the expression operator
     * @param _operator The expression operator
     */
    void setOperator(ExprOperator _operator)
    {
      operator_ = _operator;
    }

    /**
     * Sets the operator based on its string representation
     * @param opString The operator string symbol
     */
    void fromString(const std::string &opString);

    /**
     * Stringifies the operator
     * @return The stringified version of the operator
     */
    std::string toString();
};

#endif /* NODEEXPRESSIONOPERATOR_H_ */
