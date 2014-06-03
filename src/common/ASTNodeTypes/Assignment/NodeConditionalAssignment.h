/*
 * NodeConditionalAssignment.h
 *
 *  Created on: Jun 3, 2014
 *      Author: cmaier
 */

#ifndef NODECONDITIONALASSIGNMENT_H_
#define NODECONDITIONALASSIGNMENT_H_

#include <memory>
#include <vector>
#include <algorithm>

#include "NodeAssignmentBase.h"
#include "../Formula/NodeFormulaBase.h"

class NodeConditionalAssignment: public NodeAssignmentBase
{
  private:
    std::shared_ptr<NodeFormulaBase> formula_;
    std::vector<std::shared_ptr<NodeAssignmentBase>> assignmentsIf_;
    std::vector<std::shared_ptr<NodeAssignmentBase>> assignmentsElse_;
    bool buildElseBlock_;

  public:
    NodeConditionalAssignment();
    virtual ~NodeConditionalAssignment();

    void addAssignmentIf(const std::shared_ptr<NodeAssignmentBase>& assignment)
    {
      assignmentsIf_.push_back(assignment);
    }

    void addAssignmentElse(const std::shared_ptr<NodeAssignmentBase>& assignment)
    {
      assignmentsElse_.push_back(assignment);
    }

    void addAssignment(const std::shared_ptr<NodeAssignmentBase>& assignment)
    {
      if (buildElseBlock_)
        assignmentsElse_.push_back(assignment);
      else
        assignmentsIf_.push_back(assignment);
    }

    const std::vector<std::shared_ptr<NodeAssignmentBase> >& getAssignmentsElse() const
    {
      return assignmentsElse_;
    }

    const std::vector<std::shared_ptr<NodeAssignmentBase> >& getAssignmentsIf() const
    {
      return assignmentsIf_;
    }

    const std::shared_ptr<NodeFormulaBase>& getFormula() const
    {
      return formula_;
    }

    void setFormula(const std::shared_ptr<NodeFormulaBase>& formula)
    {
      formula_ = formula;
    }

    bool buildElseBlock() const
    {
      return buildElseBlock_;
    }

    void buildElseBlock(bool buildElseBlock)
    {
      buildElseBlock_ = buildElseBlock;
    }

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      visitor->visit(this);

      formula_->accept(visitor);

      std::for_each(std::begin(assignmentsIf_), std::end(assignmentsIf_),
          [&visitor](std::shared_ptr<NodeAssignmentBase> assignment)
          { assignment->accept(visitor);});

      std::for_each(std::begin(assignmentsElse_), std::end(assignmentsElse_),
          [&visitor](std::shared_ptr<NodeAssignmentBase> assignment)
          { assignment->accept(visitor);});
    }
};

#endif /* NODECONDITIONALASSIGNMENT_H_ */
