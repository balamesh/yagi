/**
 * @file   NodeForLoop.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for a YAGI for-loop
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


#ifndef NODEFORLOOP_H_
#define NODEFORLOOP_H_

#include <memory>

#include "NodeStatementBase.h"
#include "NodeBlock.h"
#include "../Expressions/NodeSetExpression.h"
#include "../Tuple/NodeTuple.h"

/**
 * AST node class for a YAGI for-loop of the form 'foreach' <tuple> 'in' <setexpr> 'do'...
 */
class NodeForLoop: public NodeStatementBase
{
  private:
    /**
     * The foreach-tuple
     */
    std::shared_ptr<NodeTuple> tuple_;

    /**
     * The set the tuple gets picked from
     */
    std::shared_ptr<NodeSetExpression> setExpr_;

    /**
     * The block to be executed w.r.t. the picked tuple
     */
    std::shared_ptr<NodeBlock> block_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeForLoop();

    /**
     * Default dtor
     */
    virtual ~NodeForLoop();

    /**
     * Getter for the block to be executed
     * @return The block to be executed
     */
    const std::shared_ptr<NodeBlock>& getBlock() const
    {
      return block_;
    }

    /**
     * Setter for the block to be executed
     * @param block The block to be executed
     */
    void setBlock(const std::shared_ptr<NodeBlock>& block)
    {
      block_ = block;
    }

    /**
     * Getter for the set from which a tuple gets picked from
     * @return The set
     */
    const std::shared_ptr<NodeSetExpression>& getSetExpr() const
    {
      return setExpr_;
    }

    /**
     * Setter for the set from which a tuple gets picked from
     * @param setExpr The set
     */
    void setSetExpr(const std::shared_ptr<NodeSetExpression>& setExpr)
    {
      setExpr_ = setExpr;
    }

    /**
     * Getter for the picked tuple
     * @return The tuple
     */
    const std::shared_ptr<NodeTuple>& getTuple() const
    {
      return tuple_;
    }

    /**
     * Setter for the picked tuple
     * @param tuple The picked tuple
     */
    void setTuple(const std::shared_ptr<NodeTuple>& tuple)
    {
      tuple_ = tuple;
    }
};

#endif /* NODEFORLOOP_H_ */
