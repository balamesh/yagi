/*
 * NodePassiveSensingDecl.h
 *
 *  Created on: Jun 4, 2014
 *      Author: cmaier
 */

#ifndef NODEPASSIVESENSINGDECL_H_
#define NODEPASSIVESENSINGDECL_H_

#include <string>
#include <memory>
#include <vector>
#include <algorithm>

#include "../../Variables/NodeVarList.h"
#include "../../Identifier/NodeID.h"
#include "../../Assignment/NodeAssignmentBase.h"

class NodePassiveSensingDecl: public ASTNodeBase<>
{
  private:
    std::shared_ptr<NodeID> passiveSensingName_;
    std::shared_ptr<NodeVarList> argList_;
    std::vector<std::shared_ptr<NodeAssignmentBase>> assignments_;
  public:
    DEFINE_VISITABLE()
    NodePassiveSensingDecl();
    virtual ~NodePassiveSensingDecl();

    const std::shared_ptr<NodeVarList>& getArgList() const
    {
      return argList_;
    }

    void setArgList(const std::shared_ptr<NodeVarList>& argList)
    {
      argList_ = argList;
    }

    const std::vector<std::shared_ptr<NodeAssignmentBase> >& getAssignments() const
    {
      return assignments_;
    }

    const std::shared_ptr<NodeID>& getPassiveSensingName() const
    {
      return passiveSensingName_;
    }

    void setPassiveSensingName(const std::shared_ptr<NodeID>& passiveSensingName)
    {
      passiveSensingName_ = passiveSensingName;
    }

    void addAssignment(const std::shared_ptr<NodeAssignmentBase>& assignment)
    {
      assignments_.push_back(assignment);
    }

//    virtual void accept(ASTNodeVisitorBase* visitor) override
//    {
//      visitor->visit(this);
//
//      passiveSensingName_->accept(visitor);
//      if (argList_ != nullptr)
//        argList_->accept(visitor);
//
//      std::for_each(std::begin(assignments_), std::end(assignments_),
//          [&visitor](std::shared_ptr<NodeAssignmentBase> assignment)
//          { assignment->accept(visitor);});
//    }
};

#endif /* NODEPASSIVESENSINGDECL_H_ */
