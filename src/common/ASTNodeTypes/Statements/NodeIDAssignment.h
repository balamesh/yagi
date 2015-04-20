/**
 * @file   NodeIDAssignment.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for a YAGI assignment
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


#ifndef NODEIDASSIGNMENT_H_
#define NODEIDASSIGNMENT_H_

#include "../../ASTNodeTypes/Identifier/NodeID.h"
#include "../../ASTNodeTypes/Expressions/NodeSetExpression.h"
#include "../../ASTNodeTypes/Statements/NodeAssignmentOperator.h"
#include "NodeStatementBase.h"

#include <memory>

/**
 * AST node class for a YAGI assignment to an ID, i.e. to a fluent
 */
class NodeIDAssignment: public NodeStatementBase
{
  private:
    /**
     * The name of the fluent
     */
    std::shared_ptr<NodeID> fluentName_;

    /**
     * The assignment operator
     */
    std::shared_ptr<NodeAssignmentOperator> operator_;

    /**
     * The set to be assigned
     */
    std::shared_ptr<NodeSetExpression> setExpr_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeIDAssignment();

    /**
     * Default dtor
     */
    virtual ~NodeIDAssignment();

    /**
     * Getter for the fluent to be assigned to
     * @return The name of the fluent
     */
    const std::shared_ptr<NodeID>& getFluentName() const
    {
      return fluentName_;
    }

    /**
     * Setter for the fluent to be assigned to
     * @param fluentName The name of the fluent
     */
    void setFluentName(const std::shared_ptr<NodeID>& fluentName)
    {
      fluentName_ = fluentName;
    }

    /**
     * Getter for the assignment operator
     * @return The assignment operator
     */
    const std::shared_ptr<NodeAssignmentOperator>& getOperator() const
    {
      return operator_;
    }

    /**
     * Settter for the assignment operator
     * @param _operator The assignment operator
     */
    void setOperator(const std::shared_ptr<NodeAssignmentOperator>& _operator)
    {
      operator_ = _operator;
    }

    /**
     * Getter for the set to be assigned
     * @return The set to be assigned
     */
    const std::shared_ptr<NodeSetExpression>& getSetExpr() const
    {
      return setExpr_;
    }

    /**
     * Setter for the set to be assigned
     * @param setExpr The set to be assigned
     */
    void setSetExpr(const std::shared_ptr<NodeSetExpression>& setExpr)
    {
      setExpr_ = setExpr;
    }
};

#endif /* NODEIDASSIGNMENT_H_ */
