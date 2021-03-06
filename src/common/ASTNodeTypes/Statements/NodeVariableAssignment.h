/**
 * @file   NodeVariableAssignment.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for YAGI assignments to variables
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


#ifndef NODEVARIABLEASSIGNMENT_H_
#define NODEVARIABLEASSIGNMENT_H_

#include <memory>

#include "../Variables/NodeVariable.h"
#include "../Expressions/NodeValueExpression.h"
#include "NodeStatementBase.h"

/**
 * AST node class for YAGI assignments to variables
 */
class NodeVariableAssignment: public NodeStatementBase
{
  private:
    /**
     * The name of the variable
     */
    std::shared_ptr<NodeVariable> variable_;

    /**
     * The value to be assigned
     */
    std::shared_ptr<ASTNodeBase<>> value_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeVariableAssignment();

    /**
     * Default dtor
     */
    virtual ~NodeVariableAssignment();

    /**
     * Getter for the variable
     * @return The variable
     */
    const std::shared_ptr<NodeVariable>& getVariable() const
    {
      return variable_;
    }

    /**
     * Setter for the variable
     * @param variable The variable
     */
    void setVariable(const std::shared_ptr<NodeVariable>& variable)
    {
      variable_ = variable;
    }

    /**
     * Getter for the value to assign
     * @return The value
     */
    const std::shared_ptr<ASTNodeBase<> >& getValue() const
    {
      return value_;
    }

    /**
     * Setter for the value to assign
     * @param value The value to assign
     */
    void setValue(const std::shared_ptr<ASTNodeBase<> >& value)
    {
      value_ = value;
    }
};

#endif /* NODEVARIABLEASSIGNMENT_H_ */
