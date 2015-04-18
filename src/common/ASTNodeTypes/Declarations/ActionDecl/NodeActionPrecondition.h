/**
 * @file   NodeActionPrecondition.h
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * AST node for action preconditions.
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


#ifndef NODEACTIONPRECONDITION_H_
#define NODEACTIONPRECONDITION_H_

#include <memory>

#include "../../ASTNodeBase.h"
#include "../../Formula/NodeFormulaBase.h"

/**
 * AST node class for action preconditions.
 */
class NodeActionPrecondition: public ASTNodeBase<>
{
  private:
    /**
     * The precondition formula
     */
    std::shared_ptr<NodeFormulaBase> formula_;
  public:
    DEFINE_VISITABLE()

    /**
     * Ctor with action precondition formula
     */
    NodeActionPrecondition(const std::shared_ptr<NodeFormulaBase>& formula);

    /**
     * Default ctor
     */
    NodeActionPrecondition();

    /**
     * Default dtor
     */
    virtual ~NodeActionPrecondition();

    /**
     * Getter for action precondition formula
     * @return The formula node
     */
    const std::shared_ptr<NodeFormulaBase>& getFormula() const
    {
      return formula_;
    }

    /**
     * Setter for action precondition formula
     * @param formula The formula node
     */
    void setFormula(const std::shared_ptr<NodeFormulaBase>& formula)
    {
      formula_ = formula;
    }
};

#endif /* NODEACTIONPRECONDITION_H_ */
