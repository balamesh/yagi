/**
 * @file   NodeSet.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for a set of tuples
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


#ifndef NODESET_H_
#define NODESET_H_

#include <vector>
#include <memory>

#include "../ASTNodeBase.h"
#include "../../ASTNodeTypes/Tuple/NodeTuple.h"

/**
 * AST node class for a set of tuples
 */
class NodeSet: public ASTNodeBase<>
{
  private:
    /**
     * The tuples in the set
     */
    std::vector<std::shared_ptr<NodeTuple>> tuples_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeSet();

    /**
     * Default dtor
     */
    virtual ~NodeSet();

    /**
     * Getter for the tuples
     * @return The tuples in the set
     */
    const std::vector<std::shared_ptr<NodeTuple>>& getTuples() const
    {
      return tuples_;
    }

    /**
     * Adds a tuple to the set
     * @param tuple The tuple to be added
     */
    void addTuple(const std::shared_ptr<NodeTuple>& tuple)
    {
      tuples_.push_back(tuple);
    }
};

#endif /* NODESET_H_ */
