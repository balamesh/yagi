/**
 * @file   NodeConstant.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for logical constants
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


#ifndef NODECONSTANT_H_
#define NODECONSTANT_H_

#include <string>
#include <stdexcept>

#include "NodeFormulaBase.h"

/**
 * AST node class for logical constants
 */
class NodeConstant: public NodeFormulaBase
{
  private:

    /**
     * The truth value of the constant
     */
    bool truthValue_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeConstant();

    /**
     * Default dtor
     */
    virtual ~NodeConstant();

    /**
     * Getter for the truth value
     * @return The truth value
     */
    bool getTruthValue() const
    {
      return truthValue_;
    }

    /**
     * Setter for the truth value
     * @param truthValue The truth value
     */
    void setTruthValue(bool truthValue)
    {
      truthValue_ = truthValue;
    }

    /**
     * Parses truth value from string representation
     * @param truthVal The string rep. of the truth value
     */
    void fromString(const std::string& truthVal);
};

#endif /* NODECONSTANT_H_ */
