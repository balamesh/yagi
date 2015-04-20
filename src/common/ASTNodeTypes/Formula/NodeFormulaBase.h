/**
 * @file   NodeFormulaBase.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for base formula
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


#ifndef NODEFORMULABASE_H_
#define NODEFORMULABASE_H_

#include "../ASTNodeBase.h"

/**
 * AST node class for base formula
 */
class NodeFormulaBase: public ASTNodeBase<>
{
  public:
    /**
     * Default ctor
     */
    NodeFormulaBase();

    /**
     * Default dtor
     */
    virtual ~NodeFormulaBase();
};

#endif /* NODEFORMULABASE_H_ */
