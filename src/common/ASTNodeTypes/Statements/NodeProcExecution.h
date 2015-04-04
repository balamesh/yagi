/**
 * @file   NodeProcExecution.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for a YAGI procedure execution
 */

#ifndef NODEPROCEXECUTION_H_
#define NODEPROCEXECUTION_H_

#include "NodeStatementBase.h"
#include "../Identifier/NodeID.h"
#include "../DataTypes/NodeValueList.h"

#include <memory>

/**
 * AST node class for a YAGI procedure execution
 */
class NodeProcExecution: public NodeStatementBase
{
  private:
    /**
     * Name of the proc. to be executed
     */
    std::shared_ptr<NodeID> procToExecName_;

    /**
     * Argument list
     */
    std::shared_ptr<NodeValueList> parameters_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeProcExecution();

    /**
     * Default dtor
     */
    virtual ~NodeProcExecution();

    /**
     * Getter for the proc. name
     * @return The name of the proc.
     */
    const std::shared_ptr<NodeID>& getProcToExecName() const
    {
      return procToExecName_;
    }

    /**
     * Setter for the proc. name
     * @param procToExecName The name of the proc.
     */
    void setProcToExecName(const std::shared_ptr<NodeID>& procToExecName)
    {
      procToExecName_ = procToExecName;
    }

    /**
     * Getter for the argument list
     * @return The list of arguments
     */
    const std::shared_ptr<NodeValueList>& getParameters() const
    {
      return parameters_;
    }

    /**
     * Setter for the argument list
     * @param parameters The list of arguments
     */
    void setParameters(const std::shared_ptr<NodeValueList>& parameters)
    {
      parameters_ = parameters;
    }
};

#endif /* NODEPROCEXECUTION_H_ */
