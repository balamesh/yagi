/**
 * @file   NodeAssignmentOperator.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for assignment operators
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


#ifndef NODEASSIGNMENTOPERATOR_H_
#define NODEASSIGNMENTOPERATOR_H_

#include <string>
#include <stdexcept>

#include "../ASTNodeBase.h"

/**
 * The types of assignment operators
 */
enum class AssignmentOperator
{
  Assign, AddAssign, RemoveAssign, Unknown
};

/**
 * AST node class for assignment operators
 */
class NodeAssignmentOperator: public ASTNodeBase<>
{
  private:
    /**
     * The assignment operator
     */
    AssignmentOperator operator_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeAssignmentOperator();

    /**
     * Default dtor
     */
    virtual ~NodeAssignmentOperator();

    /**
     * Getter for the assignment operator
     * @return The assignment operator
     */
    AssignmentOperator getOperator() const
    {
      return operator_;
    }

    /**
     * Setter for the assignment operator
     * @param _operator The assignment operator
     */
    void setOperator(AssignmentOperator _operator)
    {
      operator_ = _operator;
    }

    /**
     * Stringifies the assignment operator
     * @return Stringified version of the operator
     */
    std::string toString();

    /**
     * Parses the operator from its string representation
     * @param opString The operator string
     */
    void fromString(const std::string& opString);
};

#endif /* NODEASSIGNMENTOPERATOR_H_ */
