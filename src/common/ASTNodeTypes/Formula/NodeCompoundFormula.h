/**
 * @file   NodeCompoundFormula.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for compound formulas
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


#ifndef NODECOMPOUNDFORMULA_H_
#define NODECOMPOUNDFORMULA_H_

#include <memory>

#include "NodeFormulaBase.h"
#include "NodeAtom.h"
#include "NodeFormulaConnective.h"

/**
 * AST node class for compound formulas
 */
class NodeCompoundFormula: public NodeFormulaBase
{
  private:
    /**
     * Left-hand side subformula
     */
    std::shared_ptr<NodeFormulaBase> leftOperand_;

    /**
     * Formula connective
     */
    std::shared_ptr<NodeFormulaConnective> connective_;

    /**
     * Right-hand side subformula
     */
    std::shared_ptr<NodeFormulaBase> rightOperand_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeCompoundFormula();

    /**
     * Default dtor
     */
    virtual ~NodeCompoundFormula();

    /**
     * Getter for formula connective
     * @return The formula connective
     */
    const std::shared_ptr<NodeFormulaConnective>& getConnective() const
    {
      return connective_;
    }

    /**
     * Setter for formula connective
     * @param connective The formula connective
     */
    void setConnective(const std::shared_ptr<NodeFormulaConnective>& connective)
    {
      connective_ = connective;
    }

    /**
     * Getter for the lhs subformula
     * @return The lhs subformula
     */
    const std::shared_ptr<NodeFormulaBase>& getLeftOperand() const
    {
      return leftOperand_;
    }

    /**
     * Setter for the lhs subformula
     * @param leftOperand The lhs subformula
     */
    void setLeftOperand(const std::shared_ptr<NodeFormulaBase>& leftOperand)
    {
      leftOperand_ = leftOperand;
    }

    /**
     * Getter for the rhs subformula
     * @return The rhs subformula
     */
    const std::shared_ptr<NodeFormulaBase>& getRightOperand() const
    {
      return rightOperand_;
    }

    /**
     * Setter for the rhs subformula
     * @param rightOperand The rhs subformula
     */
    void setRightOperand(const std::shared_ptr<NodeFormulaBase>& rightOperand)
    {
      rightOperand_ = rightOperand;
    }
};

#endif /* NODECOMPOUNDFORMULA_H_ */
