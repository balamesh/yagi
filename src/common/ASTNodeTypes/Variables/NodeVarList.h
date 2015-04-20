/**
 * @file   NodeVarList.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for YAGI variable lists
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


#ifndef NODEVARLIST_H_
#define NODEVARLIST_H_

#include <vector>
#include <memory>
#include <algorithm>

#include "../../ASTNodeTypes/ASTNodeBase.h"
#include "../../ASTNodeTypes/Variables/NodeVariable.h"

/**
 * AST node class for YAGI variable lists
 */
class NodeVarList: public ASTNodeBase<>
{
  private:
    /**
     * List of variables
     */
    std::vector<std::shared_ptr<NodeVariable>> variables_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeVarList();

    /**
     * Default dtor
     */
    virtual ~NodeVarList();

    /**
     * Getter for the list of variables
     * @return The list of variables
     */
    const std::vector<std::shared_ptr<NodeVariable> >& getVariables() const
    {
      return variables_;
    }

    /**
     * Adds a variable to the list
     * @param variable The variable to add
     */
    void addVariable(std::shared_ptr<NodeVariable> variable)
    {
      variables_.push_back(variable);
    }
};

#endif /* NODEVARLIST_H_ */
