/**
 * @file   NodeOperatorIn.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for "tuple-in-set" formulas
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


#ifndef NODEOPERATORIN_H_
#define NODEOPERATORIN_H_

#include <memory>

#include "../Tuple/NodeTuple.h"
#include "../Expressions/NodeSetExpression.h"

#include "NodeFormulaBase.h"

/**
 * AST node class for "tuple-in-set" formulas
 */
class NodeOperatorIn: public NodeFormulaBase
{
  private:

    /**
     * The tuple to check
     */
    std::shared_ptr<NodeTuple> tuple_;

    /**
     * The set to check
     */
    std::shared_ptr<ASTNodeBase<>> setExpr_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeOperatorIn();

    /**
     * Default dtor
     */
    virtual ~NodeOperatorIn();

    /**
     * Getter for the set to check
     * @return The set to check
     */
    const std::shared_ptr<ASTNodeBase<>>& getSetExpr() const
    {
      return setExpr_;
    }

    /**
     * Setter for the set to check
     * @param setExpr The set to check
     */
    void setSetExpr(const std::shared_ptr<ASTNodeBase<>>& setExpr)
    {
      setExpr_ = setExpr;
    }

    /**
     * Getter for the tuple to check
     * @return The tuple to check
     */
    const std::shared_ptr<NodeTuple>& getTuple() const
    {
      return tuple_;
    }

    /**
     * Setter for the tuple to check
     * @param tuple The tuple to check
     */
    void setTuple(const std::shared_ptr<NodeTuple>& tuple)
    {
      tuple_ = tuple;
    }
};

#endif /* NODEOPERATORIN_H_ */
