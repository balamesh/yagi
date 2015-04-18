/**
 * @file   NodeIncompleteKnowledge.h
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * AST node for incomplete knowledge.
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


#ifndef NODEINCOMPLETEKNOWLEDGE_H_
#define NODEINCOMPLETEKNOWLEDGE_H_

#include "../ASTNodeBase.h"

/**
 * AST node class for incomplete knowledge.
 */
class NodeIncompleteKnowledge: public ASTNodeBase<>
{
  public:
    DEFINE_VISITABLE()
    /**
     * Default ctor
     */
    NodeIncompleteKnowledge();

    /**
     * Default dtor
     */
    virtual ~NodeIncompleteKnowledge();
};

#endif /* NODEINCOMPLETEKNOWLEDGE_H_ */
