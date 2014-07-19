/*
 * VariableAssignment.h
 *
 *  Created on: May 26, 2014
 *      Author: cmaier
 */

#ifndef NODEVARIABLEASSIGNMENT_H_
#define NODEVARIABLEASSIGNMENT_H_

#include <memory>

#include "../Variables/NodeVariable.h"
#include "../Expressions/NodeValueExpression.h"
#include "NodeStatementBase.h"

class NodeVariableAssignment: public NodeStatementBase
{
  private:
    std::shared_ptr<NodeVariable> variable_;
    std::shared_ptr<ASTNodeBase<>> value_;

  public:
    DEFINE_VISITABLE()
    NodeVariableAssignment();
    virtual ~NodeVariableAssignment();

    const std::shared_ptr<NodeVariable>& getVariable() const
    {
      return variable_;
    }

    void setVariable(const std::shared_ptr<NodeVariable>& variable)
    {
      variable_ = variable;
    }

    const std::shared_ptr<ASTNodeBase<> >& getValue() const
    {
      return value_;
    }

    void setValue(const std::shared_ptr<ASTNodeBase<> >& value)
    {
      value_ = value;
    }
};

#endif /* NODEVARIABLEASSIGNMENT_H_ */
