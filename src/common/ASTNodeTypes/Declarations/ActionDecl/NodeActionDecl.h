/**
 * @file   NodeActionDecl.h
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * AST node for action declarations.
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

/**
 * AST node class for action declarations.
 */
class NodeActionDecl: public ASTNodeBase<>
{
  private:
    /**
     * Name of the action
     */
    std::shared_ptr<NodeID> actionName_;

    /**
     * List of variables passed to action
     */
    std::shared_ptr<NodeVarList> varList_;

    /**
     * List of setting variables
     */
    std::shared_ptr<NodeVarList> settingVarList_;

    /**
     * Action precondition
     */
    std::shared_ptr<NodeActionPrecondition> actionPrecondition_;

    /**
     * Action effect
     */
    std::shared_ptr<NodeActionEffect> actionEffect_;

    /**
     * Signal
     */
    std::shared_ptr<NodeSignal> signal_;
  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeActionDecl();

    /**
     * Default dtor
     */
    virtual ~NodeActionDecl();

    /**
     * Getter for the action effect
     * @return The action effect node
     */
    const std::shared_ptr<NodeActionEffect>& getActionEffect() const
    {
      return actionEffect_;
    }

    /**
     * Setter for the action effect
     * @param actionEffect The action effect node
     */
    void setActionEffect(const std::shared_ptr<NodeActionEffect>& actionEffect)
    {
      actionEffect_ = actionEffect;
    }

    /**
     * Getter for the action name
     * @return The node of the action name
     */
    const std::shared_ptr<NodeID>& getActionName() const
    {
      return actionName_;
    }

    /**
     * Setter for the action name
     * @param actionName The node of the action name
     */
    void setActionName(const std::shared_ptr<NodeID>& actionName)
    {
      actionName_ = actionName;
    }

    /**
     * Getter for the action precondition
     * @return The action precondition node
     */
    const std::shared_ptr<NodeActionPrecondition>& getActionPrecondition() const
    {
      return actionPrecondition_;
    }

    /**
     * Setter for the action precondition
     * @param actionPrecondition The action precondition node
     */
    void setActionPrecondition(const std::shared_ptr<NodeActionPrecondition>& actionPrecondition)
    {
      actionPrecondition_ = actionPrecondition;
    }

    /**
     * Getter for the signal
     * @return The signal node
     */
    const std::shared_ptr<NodeSignal>& getSignal() const
    {
      return signal_;
    }

    /**
     * Setter for the signal
     * @param signal The signal node
     */
    void setSignal(const std::shared_ptr<NodeSignal>& signal)
    {
      signal_ = signal;
    }

    /**
     * Getter for the variable list
     * @return The variable list node
     */
    const std::shared_ptr<NodeVarList>& getVarList() const
    {
      return varList_;
    }

    /**
     * Setter for the variable list
     * @param varList The variable list node
     */
    void setVarList(const std::shared_ptr<NodeVarList>& varList)
    {
      varList_ = varList;
    }

    /**
     * Getter for the setting variable list
     * @return The setting variable list node
     */
    const std::shared_ptr<NodeVarList>& getSettingVarList() const
    {
      return settingVarList_;
    }

    /**
     * Setter for the setting variable list
     * @param settingVarList The setting variable list node
     */
    void setSettingVarList(const std::shared_ptr<NodeVarList>& settingVarList)
    {
      settingVarList_ = settingVarList;
    }
};

#endif /* NODEACTIONDECL_H_ */
