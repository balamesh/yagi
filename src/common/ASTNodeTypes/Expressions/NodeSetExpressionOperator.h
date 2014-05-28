/*
 * NodeSetExpressionOperator.h
 *
 *  Created on: May 27, 2014
 *      Author: cmaier
 */

#ifndef NODESETEXPRESSIONOPERATOR_H_
#define NODESETEXPRESSIONOPERATOR_H_

#include <string>
#include <stdexcept>

#include "../ASTNodeBase.h"

enum class SetExprOperator
{
  Assign, AddAssign, RemoveAssign, Unknown
};

class NodeSetExpressionOperator: public ASTNodeBase
{
  private:
    SetExprOperator operator_;

  public:
    NodeSetExpressionOperator();
    virtual ~NodeSetExpressionOperator();

    SetExprOperator getOperator() const
    {
      return operator_;
    }

    void setOperator(SetExprOperator _operator)
    {
      operator_ = _operator;
    }

    void fromString(std::string opString)
    {
      if (opString == "=")
        operator_ = SetExprOperator::Assign;
      else if (opString == "+=")
        operator_ = SetExprOperator::AddAssign;
      else if (opString == "-=")
        operator_ = SetExprOperator::RemoveAssign;
      else
        throw std::runtime_error("Invalid set expression operator string '" + opString + "'!");
    }

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      visitor->visit(this);
    }
};

#endif /* NODESETEXPRESSIONOPERATOR_H_ */
