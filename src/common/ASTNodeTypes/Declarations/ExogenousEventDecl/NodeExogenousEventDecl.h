/*
 * NodeExogenousEventDecl.h
 *
 *  Created on: Jun 4, 2014
 *      Author: cmaier
 */

#ifndef NODEEXOGENOUSEVENTDECL_H_
#define NODEEXOGENOUSEVENTDECL_H_

#include <string>
#include <memory>
#include <vector>
#include <algorithm>

#include "../../Variables/NodeVarList.h"
#include "../../Identifier/NodeID.h"
#include "../../Statements/NodeBlock.h"

class NodeExogenousEventDecl: public ASTNodeBase<>
{
  private:
    std::shared_ptr<NodeID> exoEventName_;
    std::shared_ptr<NodeVarList> argList_;
    std::shared_ptr<NodeBlock> block_;
  public:
    DEFINE_VISITABLE()
    NodeExogenousEventDecl();
    virtual ~NodeExogenousEventDecl();

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

    const std::shared_ptr<NodeID>& getExogenousEventName() const
    {
      return exoEventName_;
    }

    void setExogenousEventName(const std::shared_ptr<NodeID>& exoEgentName)
    {
      exoEventName_ = exoEgentName;
    }

    void setBlock(const std::shared_ptr<NodeBlock>& block)
    {
      block_ = block;
    }
};

#endif /* NODEEXOGENOUSEVENTDECL_H_ */
