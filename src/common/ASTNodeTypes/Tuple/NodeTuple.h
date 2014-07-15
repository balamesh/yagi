/*
 * NodeTuple.h
 *
 *  Created on: May 28, 2014
 *      Author: cmaier
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

class NodeTuple: public ASTNodeBase<>
{
  private:
    std::vector<std::shared_ptr<ASTNodeBase<>>> tupleValues_;

    bool isPassedTypeValid(const std::shared_ptr<ASTNodeBase<>>& tupleVal);

  public:
    DEFINE_VISITABLE()
    NodeTuple();
    virtual ~NodeTuple();

    void addTupleValue(std::shared_ptr<ASTNodeBase<>> tupleVal)
    {
      if (isPassedTypeValid(tupleVal))
        tupleValues_.push_back(tupleVal);
      else
        throw std::runtime_error("Invalid Type passed as TupleValue");
    }

    const std::vector<std::shared_ptr<ASTNodeBase<>>>& getTupleValues() const
    {
      return tupleValues_;
    }
};

#endif /* NODETUPLE_H_ */
