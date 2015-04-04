/**
 * @file   NodeProcDecl.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for procedure declarations.
 */

#ifndef NODEPROCDECL_H_
#define NODEPROCDECL_H_

#include <string>
#include <memory>
#include <vector>
#include <algorithm>

#include "../../Variables/NodeVarList.h"
#include "../../Identifier/NodeID.h"
#include "../../Statements/NodeBlock.h"

/**
 * AST node class for procedure declarations.
 */
class NodeProcDecl: public ASTNodeBase<>
{
  private:
    /**
     * Name of the procedure
     */
    std::shared_ptr<NodeID> procName_;

    /**
     * List of procedure arguments
     */
    std::shared_ptr<NodeVarList> argList_;

    /**
     * Block to execute
     */
    std::shared_ptr<NodeBlock> block_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeProcDecl();

    /**
     * Default dtor
     */
    virtual ~NodeProcDecl();

    /**
     * Getter for arg list
     * @return The arg list of the procedure
     */
    const std::shared_ptr<NodeVarList>& getArgList() const
    {
      return argList_;
    }

    /**
     * Setter for arg list
     * @param argList The arg list of the procedure
     */
    void setArgList(const std::shared_ptr<NodeVarList>& argList)
    {
      argList_ = argList;
    }

    /**
     * Getter for the block
     * @return The block to be executed
     */
    const std::shared_ptr<NodeBlock>& getBlock() const
    {
      return block_;
    }

    /**
     * Setter for the block
     * @param block The block to be executed
     */
    void setBlock(const std::shared_ptr<NodeBlock>& block)
    {
      block_ = block;
    }

    /**
     * Getter for the proc name
     * @return The name of the proc
     */
    const std::shared_ptr<NodeID>& getProcName() const
    {
      return procName_;
    }

    /**
     * Setter for the proc name
     * @param procName The name of the proc
     */
    void setProcName(const std::shared_ptr<NodeID>& procName)
    {
      procName_ = procName;
    }
};

#endif /* NODEPROCDECL_H_ */
