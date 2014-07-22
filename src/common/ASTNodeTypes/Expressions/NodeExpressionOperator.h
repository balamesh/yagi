/*
 * NodeExpressionOperator.h
 *
 *  Created on: May 26, 2014
 *      Author: cmaier
 */

#ifndef NODEEXPRESSIONOPERATOR_H_
#define NODEEXPRESSIONOPERATOR_H_

#include <string>
#include <stdexcept>

#include "../ASTNodeBase.h"

enum class ExprOperator
{
  Plus, Minus, Unknown
};

class NodeExpressionOperator: public ASTNodeBase<>
{
  private:
    ExprOperator operator_;

  public:
    DEFINE_VISITABLE()
    NodeExpressionOperator();
    virtual ~NodeExpressionOperator();

    ExprOperator getOperator() const
    {
      return operator_;
    }

    void setOperator(ExprOperator _operator)
    {
      operator_ = _operator;
    }

    void fromString(const std::string &opString);
    std::string toString();
};

#endif /* NODEEXPRESSIONOPERATOR_H_ */
