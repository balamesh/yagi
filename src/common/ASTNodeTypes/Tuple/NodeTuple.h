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

#include <vector>
#include <memory>
#include <algorithm>

class NodeTuple: public ASTNodeBase
{
  private:
    std::vector<std::shared_ptr<ASTNodeBase>> tupleValues_;

    bool isPassedTypeValid(const std::shared_ptr<ASTNodeBase>& tupleVal);

  public:
    NodeTuple();
    virtual ~NodeTuple();

    void addTupleValue(std::shared_ptr<ASTNodeBase> tupleVal)
    {
      if (isPassedTypeValid(tupleVal))
        tupleValues_.push_back(tupleVal);
      else
        throw std::runtime_error("Invalid Type passed as TupleValue");
    }

    const std::vector<std::shared_ptr<ASTNodeBase>>& getTupleValues() const
    {
      return tupleValues_;
    }

//    void setTupleValues(const std::vector<ASTNodeBase>& tupleValues)
//    {
//      tupleValues_ = tupleValues;
//    }

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      visitor->visit(this);

      std::for_each(std::begin(tupleValues_), std::end(tupleValues_),
          [&visitor](std::shared_ptr<ASTNodeBase> tupleVal)
          { tupleVal->accept(visitor);});
    }
};

#endif /* NODETUPLE_H_ */
