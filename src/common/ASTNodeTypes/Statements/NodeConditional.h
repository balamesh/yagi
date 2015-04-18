/**
 * @file   NodeConditional.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for a YAGI conditional
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


#ifndef NODECONDITIONAL_H_
#define NODECONDITIONAL_H_

#include <memory>

#include "NodeStatementBase.h"
#include "../Formula/NodeFormulaBase.h"
#include "NodeBlock.h"

/**
 * AST node class for a YAGI conditional
 */
class NodeConditional: public NodeStatementBase
{
  private:

    /**
     * The formula of the condition
     */
    std::shared_ptr<NodeFormulaBase> formula_;

    /**
     * The block that gets executed if the condition holds
     */
    std::shared_ptr<NodeBlock> ifBlock_;

    /**
     * The block that gets executed if the condition doesn't hold
     */
    std::shared_ptr<NodeBlock> elseBlock_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeConditional();

    /**
     * Default dtor
     */
    virtual ~NodeConditional();

    /**
     * Getter for the else-block
     * @return The else-block
     */
    const std::shared_ptr<NodeBlock>& getElseBlock() const
    {
      return elseBlock_;
    }

    /**
     * Setter for the else-block
     * @param elseBlock The else-block
     */
    void setElseBlock(const std::shared_ptr<NodeBlock>& elseBlock)
    {
      elseBlock_ = elseBlock;
    }

    /**
     * Getter for the condition
     * @return The condition formula
     */
    const std::shared_ptr<NodeFormulaBase>& getFormula() const
    {
      return formula_;
    }

    /**
     * Setter for the condition
     * @param formula The condition formula
     */
    void setFormula(const std::shared_ptr<NodeFormulaBase>& formula)
    {
      formula_ = formula;
    }

    /**
     * Getter for the if-block
     * @return The if-block
     */
    const std::shared_ptr<NodeBlock>& getIfBlock() const
    {
      return ifBlock_;
    }

    /**
     * Setter for the if-block
     * @param ifBlock The if-block
     */
    void setIfBlock(const std::shared_ptr<NodeBlock>& ifBlock)
    {
      ifBlock_ = ifBlock;
    }
};

#endif /* NODECONDITIONAL_H_ */
