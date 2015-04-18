/**
 * @file   NodeChoose.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for the choose statement
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


#ifndef NODECHOOSE_H_
#define NODECHOOSE_H_

#include <memory>
#include <vector>
#include <algorithm>

#include "NodeStatementBase.h"
#include "NodeBlock.h"

/**
 * AST node class for the choose statement
 */
class NodeChoose: public NodeStatementBase
{
  private:
    /**
     * Set of blocks from which one can be chosen
     */
    std::vector<std::shared_ptr<NodeBlock>> blocks_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeChoose();

    /**
     * Default dtor
     */
    virtual ~NodeChoose();

    /**
     * Getter for the blocks from which can be chosen from
     * @return The blocks from which can be chosen from
     */
    const std::vector<std::shared_ptr<NodeBlock> >& getBlocks() const
    {
      return blocks_;
    }

    /**
     * Adds a block to the set of blocks from which can be chosen from
     * @param block A block
     */
    void addBlock(const std::shared_ptr<NodeBlock>& block)
    {
      blocks_.push_back(block);
    }
};

#endif /* NODECHOOSE_H_ */
