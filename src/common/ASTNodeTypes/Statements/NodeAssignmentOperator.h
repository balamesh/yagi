/*
 * NodeAssignmentOperator.h
 *
 *  Created on: May 27, 2014
 *      Author: cmaier
 */

#ifndef NODEASSIGNMENTOPERATOR_H_
#define NODEASSIGNMENTOPERATOR_H_

#include <string>
#include <stdexcept>

#include "../ASTNodeBase.h"

enum class AssignmentOperator
{
  Assign, AddAssign, RemoveAssign, Unknown
};

class NodeAssignmentOperator: public ASTNodeBase<>
{
  private:
    AssignmentOperator operator_;

  public:
    DEFINE_VISITABLE()
    NodeAssignmentOperator();
    virtual ~NodeAssignmentOperator();

    AssignmentOperator getOperator() const
    {
      return operator_;
    }

    void setOperator(AssignmentOperator _operator)
    {
      operator_ = _operator;
    }

    std::string toString();
    void fromString(const std::string& opString);
};

#endif /* NODEASSIGNMENTOPERATOR_H_ */
