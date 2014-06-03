/*
 * NodeForLoopAssignment.h
 *
 *  Created on: Jun 3, 2014
 *      Author: cmaier
 */

#ifndef NODEFORLOOPASSIGNMENT_H_
#define NODEFORLOOPASSIGNMENT_H_

#include <memory>
#include <vector>

#include "NodeAssignmentBase.h"
#include "../Tuple/NodeTuple.h"
#include "../Expressions/NodeSetExpression.h"

class NodeForLoopAssignment: public NodeAssignmentBase
{
  private:
    std::shared_ptr<NodeTuple> tuple_;
    std::shared_ptr<NodeSetExpression> setExpr_;
    std::vector<std::shared_ptr<NodeAssignmentBase>> assignments_;

  public:
    NodeForLoopAssignment();
    virtual ~NodeForLoopAssignment();

    void addAssignment(const std::shared_ptr<NodeAssignmentBase>& assignment)
    {
      assignments_.push_back(assignment);
    }

    const std::vector<std::shared_ptr<NodeAssignmentBase> >& getAssignments() const
    {
      return assignments_;
    }

    const std::shared_ptr<NodeSetExpression>& getSetExpr() const
    {
      return setExpr_;
    }

    void setSetExpr(const std::shared_ptr<NodeSetExpression>& setExpr)
    {
      setExpr_ = setExpr;
    }

    const std::shared_ptr<NodeTuple>& getTuple() const
    {
      return tuple_;
    }

    void setTuple(const std::shared_ptr<NodeTuple>& tuple)
    {
      tuple_ = tuple;
    }

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      visitor->visit(this);

      tuple_->accept(visitor);
      setExpr_->accept(visitor);

      std::for_each(std::begin(assignments_), std::end(assignments_),
          [&visitor](std::shared_ptr<NodeAssignmentBase> assignment)
          { assignment->accept(visitor);});
    }
};

#endif /* NODEFORLOOPASSIGNMENT_H_ */
