/**
 * @file   NodeTuple.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for YAGI tuples
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


#ifndef NODETUPLE_H_
#define NODETUPLE_H_

#include "../ASTNodeBase.h"
#include "../../ASTNodeTypes/DataTypes/NodeString.h"
#include "../../ASTNodeTypes/Variables/NodeVariable.h"
#include "../../ASTNodeTypes/DataTypes/NodePatternMatching.h"
#include "../../ASTNodeTypes/DataTypes/NodeIncompleteKnowledge.h"

#include <vector>
#include <memory>
#include <algorithm>

/**
 * AST node class for YAGI tuples
 */
class NodeTuple: public ASTNodeBase<>
{
  private:
    /**
     * The values of the tuple
     */
    std::vector<std::shared_ptr<ASTNodeBase<>>>tupleValues_;

    /**
     * Checks whether or not the passed ASTNode is a valid tuple value
     * @param tupleVal The value to check
     * @return True if type is valid, false otherwise
     */
    bool isPassedTypeValid(const std::shared_ptr<ASTNodeBase<>>& tupleVal);

    public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeTuple();

    /**
     * Default dtor
     */
    virtual ~NodeTuple();

    /**
     * Adds a value to the tuple
     * @param tupleVal The value to add
     */
    void addTupleValue(std::shared_ptr<ASTNodeBase<>> tupleVal)
    {
      if (isPassedTypeValid(tupleVal))
      tupleValues_.push_back(tupleVal);
      else
      throw std::runtime_error("Invalid Type passed as TupleValue");
    }

    /**
     * Getter for the tuple values
     * @return The tuple values
     */
    const std::vector<std::shared_ptr<ASTNodeBase<>>>& getTupleValues() const
    {
      return tupleValues_;
    }
  };

#endif /* NODETUPLE_H_ */
