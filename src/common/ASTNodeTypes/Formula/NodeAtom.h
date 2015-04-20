/**
 * @file   NodeAtom.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for atoms
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


#ifndef NODEATOM_H_
#define NODEATOM_H_

#include <memory>

#include "NodeFormulaBase.h"
#include "NodeAtomConnective.h"

/**
 * AST node class for atoms
 */
class NodeAtom: public NodeFormulaBase
{
  private:
    /**
     * Left-hand side operand
     */
    std::shared_ptr<ASTNodeBase<>> leftOperand_;

    /**
     * Atom connective
     */
    std::shared_ptr<NodeAtomConnective> connective_;

    /**
     * Right-hand side operand
     */
    std::shared_ptr<ASTNodeBase<>> rightOperand_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeAtom();

    /**
     * Default dtor
     */
    virtual ~NodeAtom();

    /**
     * Getter for atom connective
     * @return The atom connective
     */
    const std::shared_ptr<NodeAtomConnective>& getConnective() const
    {
      return connective_;
    }

    /**
     * Setter for atom connective
     * @param connective The atom connective
     */
    void setConnective(const std::shared_ptr<NodeAtomConnective>& connective)
    {
      connective_ = connective;
    }

    /**
     * Getter for lhs operand
     * @return The lhs operand
     */
    const std::shared_ptr<ASTNodeBase<>>& getLeftOperand() const
    {
      return leftOperand_;
    }

    /**
     * Setter for lhs operand
     * @param leftOperand The lhs operand
     */
    void setLeftOperand(const std::shared_ptr<ASTNodeBase<>>& leftOperand)
    {
      leftOperand_ = leftOperand;
    }

    /**
     * Getter for rhs operand
     * @return The rhs operand
     */
    const std::shared_ptr<ASTNodeBase<>>& getRightOperand() const
    {
      return rightOperand_;
    }

    /**
     * Setter for rhs operand
     * @param rightOperand The rhs operand
     */
    void setRightOperand(const std::shared_ptr<ASTNodeBase<>>& rightOperand)
    {
      rightOperand_ = rightOperand;
    }
};

#endif /* NODEATOM_H_ */
