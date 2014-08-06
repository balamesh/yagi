/*
 * NodeSitCalcActionExecution.h
 *
 *  Created on: Aug 6, 2014
 *      Author: cmaier
 */

#ifndef NODESITCALCACTIONEXECUTION_H_
#define NODESITCALCACTIONEXECUTION_H_

#include <memory>

#include "../ASTNodeBase.h"
#include "NodeStatementBase.h"

class NodeID;
class NodeValueList;

enum class SitCalcActionType
{
  AddAssign, RemoveAssign, Unknown
};

class NodeSitCalcActionExecution: public NodeStatementBase
{
  private:
    std::shared_ptr<NodeValueList> parameters_;
    SitCalcActionType actionType_;
    std::shared_ptr<NodeID> fluentName_;

  public:
    DEFINE_VISITABLE()
    NodeSitCalcActionExecution();
    virtual ~NodeSitCalcActionExecution();

    SitCalcActionType getActionType() const
    {
      return actionType_;
    }

    void setActionType(SitCalcActionType actionType)
    {
      actionType_ = actionType;
    }

    const std::shared_ptr<NodeValueList>& getParameters() const
    {
      return parameters_;
    }

    void setParameters(const std::shared_ptr<NodeValueList>& parameters)
    {
      parameters_ = parameters;
    }

    const std::shared_ptr<NodeID>& getFluentName() const
    {
      return fluentName_;
    }

    void setFluentName(const std::shared_ptr<NodeID>& fluentName)
    {
      fluentName_ = fluentName;
    }
};

#endif /* NODESITCALCACTIONEXECUTION_H_ */
