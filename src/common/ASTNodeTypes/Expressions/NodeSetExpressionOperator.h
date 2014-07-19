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

class NodeSetExpressionOperator: public ASTNodeBase<>
{
  private:
    SetExprOperator operator_;

  public:
    DEFINE_VISITABLE()
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

    std::string toString();
    void fromString(const std::string& opString);
};

#endif /* NODESETEXPRESSIONOPERATOR_H_ */
