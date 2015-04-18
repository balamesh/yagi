/**
 * @file   NodeExogenousEventDecl.h
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * AST node for exogenous event declaration.
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


#ifndef NODEEXOGENOUSEVENTDECL_H_
#define NODEEXOGENOUSEVENTDECL_H_

#include <string>
#include <memory>
#include <vector>
#include <algorithm>

#include "../../Variables/NodeVarList.h"
#include "../../Identifier/NodeID.h"
#include "../../Statements/NodeBlock.h"

/**
 * AST node class for exogenous event declaration.
 */
class NodeExogenousEventDecl: public ASTNodeBase<>
{
  private:
    /**
     * Name of the exogenous event
     */
    std::shared_ptr<NodeID> exoEventName_;

    /**
     * Argument list of the exogenous event
     */
    std::shared_ptr<NodeVarList> argList_;

    /**
     * Exogenous event block
     */
    std::shared_ptr<NodeBlock> block_;
  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeExogenousEventDecl();

    /**
     * Default dtor
     */
    virtual ~NodeExogenousEventDecl();

    /**
     * Getter for exo event arglist
     * @return The variable list node
     */
    const std::shared_ptr<NodeVarList>& getArgList() const
    {
      return argList_;
    }

    /**
     * Setter for the exo event arglist
     * @param argList The variable list node
     */
    void setArgList(const std::shared_ptr<NodeVarList>& argList)
    {
      argList_ = argList;
    }

    /**
     * Getter for the exo event block
     * @return The exo event block node
     */
    const std::shared_ptr<NodeBlock>& getBlock() const
    {
      return block_;
    }

    /**
     * Getter for the exo event name
     * @return The node of the name
     */
    const std::shared_ptr<NodeID>& getExogenousEventName() const
    {
      return exoEventName_;
    }

    /**
     * Setter for the exo event name
     * @param exoEgentName The node of the name
     */
    void setExogenousEventName(const std::shared_ptr<NodeID>& exoEgentName)
    {
      exoEventName_ = exoEgentName;
    }

    /**
     * Setter for the exo event block
     * @param block The exo event block node
     */
    void setBlock(const std::shared_ptr<NodeBlock>& block)
    {
      block_ = block;
    }
};

#endif /* NODEEXOGENOUSEVENTDECL_H_ */
