/*
 * NodeProcExecution.h
 *
 *  Created on: Jun 5, 2014
 *      Author: cmaier
 */

#ifndef NODEPROCEXECUTION_H_
#define NODEPROCEXECUTION_H_

#include "NodeStatementBase.h"
#include "../Identifier/NodeID.h"
#include "../DataTypes/NodeValueList.h"

#include <memory>

class NodeProcExecution: public NodeStatementBase
{
  private:
    std::shared_ptr<NodeID> procToExecName_;
    std::shared_ptr<NodeValueList> parameters_;

  public:
    DEFINE_VISITABLE()
    NodeProcExecution();
    virtual ~NodeProcExecution();

    const std::shared_ptr<NodeID>& getProcToExecName() const
    {
      return procToExecName_;
    }

    void setProcToExecName(const std::shared_ptr<NodeID>& procToExecName)
    {
      procToExecName_ = procToExecName;
    }

    const std::shared_ptr<NodeValueList>& getParameters() const
    {
      return parameters_;
    }

    void setParameters(const std::shared_ptr<NodeValueList>& parameters)
    {
      parameters_ = parameters;
    }
};

#endif /* NODEPROCEXECUTION_H_ */
