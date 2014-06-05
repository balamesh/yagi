/*
 * NodeActionExecution.h
 *
 *  Created on: Jun 5, 2014
 *      Author: cmaier
 */

#ifndef NODEACTIONEXECUTION_H_
#define NODEACTIONEXECUTION_H_

#include "NodeStatementBase.h"
#include "../Identifier/NodeID.h"
#include "../DataTypes/NodeValueList.h"

#include <memory>

class NodeActionExecution: public NodeStatementBase
{
  private:
    std::shared_ptr<NodeID> actionToExecName_;
    std::shared_ptr<NodeValueList> parameters_;

  public:
    NodeActionExecution();
    virtual ~NodeActionExecution();

    const std::shared_ptr<NodeID>& getActionToExecName() const
    {
      return actionToExecName_;
    }

    void setActionToExecName(const std::shared_ptr<NodeID>& actionToExecName)
    {
      actionToExecName_ = actionToExecName;
    }

    const std::shared_ptr<NodeValueList>& getParameters() const
    {
      return parameters_;
    }

    void setParameters(const std::shared_ptr<NodeValueList>& parameters)
    {
      parameters_ = parameters;
    }

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      //TODO: implement this
      //visitor->visit(this);
    }
};

#endif /* NODEACTIONEXECUTION_H_ */
