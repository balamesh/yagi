/*
 * NodeProcDecl.h
 *
 *  Created on: Jun 4, 2014
 *      Author: cmaier
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

class NodeProcDecl: public ASTNodeBase
{
  private:
    std::shared_ptr<NodeID> procName_;
    std::shared_ptr<NodeVarList> argList_;
    std::shared_ptr<NodeBlock> block_;

  public:
    NodeProcDecl();
    virtual ~NodeProcDecl();

    const std::shared_ptr<NodeVarList>& getArgList() const
    {
      return argList_;
    }

    void setArgList(const std::shared_ptr<NodeVarList>& argList)
    {
      argList_ = argList;
    }

    const std::shared_ptr<NodeBlock>& getBlock() const
    {
      return block_;
    }

    void setBlock(const std::shared_ptr<NodeBlock>& block)
    {
      block_ = block;
    }

    const std::shared_ptr<NodeID>& getProcName() const
    {
      return procName_;
    }

    void setProcName(const std::shared_ptr<NodeID>& procName)
    {
      procName_ = procName;
    }

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      //TODO: implement!!
      //visitor->visit(this);

      procName_->accept(visitor);
      if (argList_ != nullptr)
        argList_->accept(visitor);

      block_->accept(visitor);
    }
};

#endif /* NODEPROCDECL_H_ */
