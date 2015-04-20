/**
 * @file   NodeBlock.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for a block of statements
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


#ifndef NODEBLOCK_H_
#define NODEBLOCK_H_

#include <vector>
#include <memory>
#include <algorithm>

#include "../ASTNodeBase.h"
#include "NodeStatementBase.h"

/**
 *  AST node class for a block of statements
 */
class NodeBlock: public ASTNodeBase<>
{
  private:
    /**
     * The set of statements in the block
     */
    std::vector<std::shared_ptr<NodeStatementBase>> statements_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeBlock();

    /**
     * Default dtor
     */
    virtual ~NodeBlock();

    /**
     * Getter for the statements in the block
     * @return The statements in the block
     */
    const std::vector<std::shared_ptr<NodeStatementBase>>& getStatements() const
    {
      return statements_;
    }

    /**
     * Adds a statement to the block
     * @param statement Statement to add
     */
    void addStatement(const std::shared_ptr<NodeStatementBase>& statement)
    {
      statements_.push_back(statement);
    }

    /**
     * Replaces a statement in a block
     * @param statement The statement used for replacement
     * @param idx The index of the statement to be replaced
     */
    void replaceStatement(std::shared_ptr<NodeStatementBase>& statement, int idx);
};

#endif /* NODEBLOCK_H_ */
