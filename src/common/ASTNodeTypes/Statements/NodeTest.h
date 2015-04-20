/**
 * @file   NodeTest.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for YAGI test-statement
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


#ifndef NODETEST_H_
#define NODETEST_H_

#include <memory>

#include "NodeStatementBase.h"
#include "../Formula/NodeFormulaBase.h"

/**
 * AST node class for YAGI test-statement
 */
class NodeTest: public NodeStatementBase
{
  private:

    /**
     * The formula to test
     */
    std::shared_ptr<NodeFormulaBase> formula_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeTest();

    /**
     * Default dtor
     */
    virtual ~NodeTest();

    /**
     * Getter for the formula to test
     * @return The formula to test
     */
    const std::shared_ptr<NodeFormulaBase>& getFormula() const
    {
      return formula_;
    }

    /**
     * Setter for the formula to test
     * @param formula The formula to test
     */
    void setFormula(const std::shared_ptr<NodeFormulaBase>& formula)
    {
      formula_ = formula;
    }
};

#endif /* NODETEST_H_ */
