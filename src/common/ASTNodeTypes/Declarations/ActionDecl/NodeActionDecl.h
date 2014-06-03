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
#include "NodeActiveSensing.h"

class NodeActionDecl: public ASTNodeBase
{
  private:
    std::shared_ptr<NodeID> actionName_;
    std::shared_ptr<NodeVarList> varList_;
    std::shared_ptr<NodeActionPrecondition> actionPrecondition_;
    std::shared_ptr<NodeActionEffect> actionEffect_;
    std::shared_ptr<NodeActiveSensing> activeSensing_;
    std::shared_ptr<NodeSignal> signal_;
  public:
    NodeActionDecl();
    virtual ~NodeActionDecl();

    const std::shared_ptr<NodeActionEffect>& getActionEffect() const
    {
      return actionEffect_;
    }

    void setActionEffect(const std::shared_ptr<NodeActionEffect>& actionEffect)
    {
      actionEffect_ = actionEffect;
    }

    const std::shared_ptr<NodeID>& getActionName() const
    {
      return actionName_;
    }

    void setActionName(const std::shared_ptr<NodeID>& actionName)
    {
      actionName_ = actionName;
    }

    const std::shared_ptr<NodeActionPrecondition>& getActionPrecondition() const
    {
      return actionPrecondition_;
    }

    void setActionPrecondition(
        const std::shared_ptr<NodeActionPrecondition>& actionPrecondition)
    {
      actionPrecondition_ = actionPrecondition;
    }

    const std::shared_ptr<NodeSignal>& getSignal() const
    {
      return signal_;
    }

    void setSignal(const std::shared_ptr<NodeSignal>& signal)
    {
      signal_ = signal;
    }

    const std::shared_ptr<NodeVarList>& getVarList() const
    {
      return varList_;
    }

    void setVarList(const std::shared_ptr<NodeVarList>& varList)
    {
      varList_ = varList;
    }

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      visitor->visit(this);

      actionName_->accept(visitor);
      if (varList_ != nullptr) varList_->accept(visitor);
      if (actionPrecondition_ != nullptr) actionPrecondition_->accept(visitor);
      if (actionEffect_ != nullptr) actionEffect_->accept(visitor);
      if (activeSensing_ != nullptr) activeSensing_->accept(visitor);
      if (signal_ != nullptr) signal_->accept(visitor);
    }

    const std::shared_ptr<NodeActiveSensing>& getActiveSensing() const
    {
      return activeSensing_;
    }

    void setActiveSensing(const std::shared_ptr<NodeActiveSensing>& activeSensing)
    {
      activeSensing_ = activeSensing;
    }
};

#endif /* NODEACTIONDECL_H_ */
