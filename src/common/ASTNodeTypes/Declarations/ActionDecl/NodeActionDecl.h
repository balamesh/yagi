/*
 * NodeActionDecl.h
 *
 *  Created on: May 23, 2014
 *      Author: cmaier
 */

#ifndef NODEACTIONDECL_H_
#define NODEACTIONDECL_H_

#include <string>
#include <memory>
#include <vector>
#include <algorithm>

#include "../../Variables/NodeVarList.h"
#include "NodeActionPrecondition.h"
#include "NodeActionEffect.h"
#include "NodeSignal.h"
#include "../../Identifier/NodeID.h"

class NodeActionDecl: public ASTNodeBase
{
  private:
    std::shared_ptr<NodeID> actionName_;
    std::shared_ptr<NodeVarList> varList_;
    std::shared_ptr<NodeActionPrecondition> actionPrecondition_;
    std::shared_ptr<NodeActionEffect> actionEffect_;
    std::shared_ptr<NodeSignal> signal_;
  public:
    NodeActionDecl();
    virtual ~NodeActionDecl();

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      visitor->visit(this);

      actionName_->accept(visitor);
      varList_->accept(visitor);
      actionPrecondition_->accept(visitor);
      actionEffect_->accept(visitor);
      signal_->accept(visitor);
    }
};

#endif /* NODEACTIONDECL_H_ */
