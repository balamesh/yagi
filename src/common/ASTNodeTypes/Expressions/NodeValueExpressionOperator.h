/*
 * ValueExpressionOperator.h
 *
 *  Created on: May 26, 2014
 *      Author: cmaier
 */

#ifndef NODEVALUEEXPRESSIONOPERATOR_H_
#define NODEVALUEEXPRESSIONOPERATOR_H_

#include <string>
#include <stdexcept>

#include "../ASTNodeBase.h"

enum class ValueExprOperator
{
  Plus, Minus, Unknown
};

class NodeValueExpressionOperator: public ASTNodeBase<>
{
  private:
    ValueExprOperator operator_;

  public:
    DEFINE_VISITABLE()
    NodeValueExpressionOperator();
    virtual ~NodeValueExpressionOperator();

    ValueExprOperator getOperator() const
    {
      return operator_;
    }

    void setOperator(ValueExprOperator _operator)
    {
      operator_ = _operator;
    }

    void fromString(const std::string &opString);
    std::string toString();
};

#endif /* NODEVALUEEXPRESSIONOPERATOR_H_ */
