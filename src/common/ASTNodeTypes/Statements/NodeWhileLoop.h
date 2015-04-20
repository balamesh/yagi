/**
 * @file   NodeWhileLoop.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for YAGI while-loops
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


#ifndef NODEWHILELOOP_H_
#define NODEWHILELOOP_H_

#include "NodeStatementBase.h"

#include "../Formula/NodeFormulaBase.h"
#include "NodeBlock.h"

/**
 * AST node class for YAGI while-loops
 */
class NodeWhileLoop: public NodeStatementBase
{
  private:
    /**
     * The while-condition formula
     */
    std::shared_ptr<NodeFormulaBase> formula_;

    /**
     * The while-block
     */
    std::shared_ptr<NodeBlock> block_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeWhileLoop();

    /**
     * Default dtor
     */
    virtual ~NodeWhileLoop();

    /**
     * Getter for the while-block
     * @return The while-block
     */
    const std::shared_ptr<NodeBlock>& getBlock() const
    {
      return block_;
    }

    /**
     * Setter for the while-block
     * @param block The while-block
     */
    void setBlock(const std::shared_ptr<NodeBlock>& block)
    {
      block_ = block;
    }

    /**
     * Getter for the while-condition
     * @return The while-condition formula
     */
    const std::shared_ptr<NodeFormulaBase>& getFormula() const
    {
      return formula_;
    }

    /**
     * Setter for the while-condition
     * @param formula The while-condition formula
     */
    void setFormula(const std::shared_ptr<NodeFormulaBase>& formula)
    {
      formula_ = formula;
    }
};

#endif /* NODEWHILELOOP_H_ */
