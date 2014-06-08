/*
 * NodeActiveSensing.h
 *
 *  Created on: Jun 3, 2014
 *      Author: cmaier
 */

#ifndef NODEACTIVESENSING_H_
#define NODEACTIVESENSING_H_

#include "../../ASTNodeBase.h"
#include "../../Assignment/NodeAssignmentBase.h"
#include "../../Variables/NodeVarList.h"

class NodeActiveSensing: public ASTNodeBase<>
{
  private:
    std::vector<std::shared_ptr<NodeAssignmentBase>> assignments_;
    std::shared_ptr<NodeVarList> varList_;

  public:
    DEFINE_VISITABLE()
    NodeActiveSensing();
    virtual ~NodeActiveSensing();

    const std::vector<std::shared_ptr<NodeAssignmentBase> >& getAssignments() const
    {
      return assignments_;
    }

    void addAssignment(const std::shared_ptr<NodeAssignmentBase>& assignment)
    {
      assignments_.push_back(assignment);
    }

    const std::shared_ptr<NodeVarList>& getVarList() const
    {
      return varList_;
    }

    void setVarList(const std::shared_ptr<NodeVarList>& varList)
    {
      varList_ = varList;
    }

//    virtual void accept(ASTNodeVisitorBase* visitor) override
//    {
//      visitor->visit(this);
//
//      if (varList_ != nullptr) varList_->accept(visitor);
//
//      std::for_each(std::begin(assignments_), std::end(assignments_),
//          [&visitor](std::shared_ptr<NodeAssignmentBase> assignment)
//          { assignment->accept(visitor);});
//    }
};

#endif /* NODEACTIVESENSING_H_ */
