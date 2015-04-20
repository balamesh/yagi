/**
 * @file   NodeNegation.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for formula negations
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


#ifndef NODENEGATION_H_
#define NODENEGATION_H_

#include <memory>

#include "NodeFormulaBase.h"

/**
 * AST node class for formula negations
 */
class NodeNegation: public NodeFormulaBase
{
  private:
    /**
     * The formula to be negated
     */
    std::shared_ptr<NodeFormulaBase> formula_;

  public:
    DEFINE_VISITABLE()
    /**
     * Default ctor
     */
    NodeNegation();

    /**
     * Default dtor
     */
    virtual ~NodeNegation();

    /**
     * Getter for the formula to be negated
     * @return The formula
     */
    const std::shared_ptr<NodeFormulaBase>& getFormula() const
    {
      return formula_;
    }

    /**
     * Setter for the formula to be negated
     * @param formula The formula
     */
    void setFormula(const std::shared_ptr<NodeFormulaBase>& formula)
    {
      formula_ = formula;
    }
};

#endif /* NODENEGATION_H_ */
