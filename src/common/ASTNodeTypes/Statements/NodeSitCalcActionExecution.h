/**
 * @file   NodeSitCalcActionExecution.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for a sit calc simple action execution
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


#ifndef NODESITCALCACTIONEXECUTION_H_
#define NODESITCALCACTIONEXECUTION_H_

#include <memory>

#include "../ASTNodeBase.h"
#include "NodeStatementBase.h"

class NodeID;
class NodeValueList;

/**
 * Types of sit calc simple actions
 */
enum class SitCalcActionType
{
  AddAssign, RemoveAssign, Unknown
};

/**
 * AST node for a sit calc simple action execution, i.e. addF or removeF
 * for each fluent F.
 */
class NodeSitCalcActionExecution: public NodeStatementBase
{
  private:
    /**
     * Parameter vector for sit calc action
     */
    std::shared_ptr<NodeValueList> parameters_;

    /**
     * Type of sit calc action
     */
    SitCalcActionType actionType_;

    /**
     * Name of fluent that gets modified
     */
    std::shared_ptr<NodeID> fluentName_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeSitCalcActionExecution();

    /**
     * Default dtor
     */
    virtual ~NodeSitCalcActionExecution();

    /**
     * Getter for sit calc action type
     * @return The sit calc action type
     */
    SitCalcActionType getActionType() const
    {
      return actionType_;
    }

    /**
     * Setter fo rsit calc action type
     * @param actionType The sit calc action type
     */
    void setActionType(SitCalcActionType actionType)
    {
      actionType_ = actionType;
    }

    /**
     * Getter for parameter vector
     * @return The parameters of the action
     */
    const std::shared_ptr<NodeValueList>& getParameters() const
    {
      return parameters_;
    }

    /**
     * Setter for parameter vector
     * @param parameters The parameters of the action
     */
    void setParameters(const std::shared_ptr<NodeValueList>& parameters)
    {
      parameters_ = parameters;
    }

    /**
     * Getter for the fluent name
     * @return The name of the fluent
     */
    const std::shared_ptr<NodeID>& getFluentName() const
    {
      return fluentName_;
    }

    /**
     * Setter for the fluent name
     * @param fluentName The name of the fluent
     */
    void setFluentName(const std::shared_ptr<NodeID>& fluentName)
    {
      fluentName_ = fluentName;
    }
};

#endif /* NODESITCALCACTIONEXECUTION_H_ */
