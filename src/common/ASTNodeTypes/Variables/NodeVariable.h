/**
 * @file   NodeVariable.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for YAGI variables
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


#ifndef NODEVARIABLE_H_
#define NODEVARIABLE_H_

#include "../../ASTNodeTypes/ASTNodeBase.h"
#include <string>

/**
 * AST node class for YAGI variables
 */
class NodeVariable: public ASTNodeBase<>
{
  private:

    /**
     * The name of the variable
     */
    std::string varName_;
  public:
    DEFINE_VISITABLE()

    /**
     * Ctor
     */
    NodeVariable(const std::string& varName);

    /**
     * Default ctor
     */
    NodeVariable();

    /**
     * Default dtor
     */
    virtual ~NodeVariable();

    /**
     * Getter for the variable name
     * @return The name of the variable
     */
    const std::string& getVarName() const
    {
      return varName_;
    }

    /**
     * Setter for the variable name
     * @param varName The name of the variable
     */
    void setVarName(const std::string& varName)
    {
      varName_ = varName;
    }
};

#endif /* NODEVARIABLE_H_ */
