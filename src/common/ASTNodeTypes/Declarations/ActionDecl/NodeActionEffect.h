/*
 * NodeActionEffect.h
 *
 *  Created on: May 23, 2014
 *      Author: cmaier
 */

#ifndef NODEACTIONEFFECT_H_
#define NODEACTIONEFFECT_H_

#include <memory>
#include <vector>
#include <algorithm>

#include "../../ASTNodeBase.h"
#include "../../Statements/NodeStatementBase.h"

class NodeActionEffect: public ASTNodeBase<>
{
  private:
    std::vector<std::shared_ptr<NodeStatementBase>> assignments_;
  public:
    DEFINE_VISITABLE()
    NodeActionEffect();
    virtual ~NodeActionEffect();

    const std::vector<std::shared_ptr<NodeStatementBase> >& getAssignments() const
    {
      return assignments_;
    }

    void addAssignment(const std::shared_ptr<NodeStatementBase>& assignment)
    {
      assignments_.push_back(assignment);
    }

//    virtual void accept(ASTNodeVisitorBase* visitor) override
//    {
//      visitor->visit(this);
//
//      std::for_each(std::begin(assignments_), std::end(assignments_),
//          [&visitor](std::shared_ptr<NodeAssignmentBase> assignment)
//          { assignment->accept(visitor);});
//    }
};

#endif /* NODEACTIONEFFECT_H_ */
