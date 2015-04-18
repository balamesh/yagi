/**
 * @file   NodePick.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for a YAGI pick-statement
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


#ifndef NODEPICK_H_
#define NODEPICK_H_

#include <memory>

#include "NodeStatementBase.h"
#include "NodeBlock.h"
#include "../Expressions/NodeSetExpression.h"
#include "../Tuple/NodeTuple.h"

/**
 * AST node for a YAGI pick-statement
 */
class NodePick: public NodeStatementBase
{
  private:
    /**
     * The tuple the picked values get bound to
     */
    std::shared_ptr<NodeTuple> tuple_;

    /**
     * The set from which values get picked from
     */
    std::shared_ptr<NodeSetExpression> setExpr_;

    /**
     * The block that gets executed w.r.t the picked tuple
     */
    std::shared_ptr<NodeBlock> block_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodePick();

    /**
     * Default dtor
     */
    virtual ~NodePick();

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
     * Getter for the set from which the tuple gets picked
     * @return The set
     */
    const std::shared_ptr<NodeSetExpression>& getSetExpr() const
    {
      return setExpr_;
    }

    /**
     * Setter for the set from which the tuple gets picked
     * @param setExpr The set
     */
    void setSetExpr(const std::shared_ptr<NodeSetExpression>& setExpr)
    {
      setExpr_ = setExpr;
    }

    /**
     * Getter for the tuple that stores the picked values
     * @return The tuple
     */
    const std::shared_ptr<NodeTuple>& getTuple() const
    {
      return tuple_;
    }

    /**
     * Setter for the tuple that stores the picked values
     * @param tuple The tuple
     */
    void setTuple(const std::shared_ptr<NodeTuple>& tuple)
    {
      tuple_ = tuple;
    }
};

#endif /* NODEPICK_H_ */
