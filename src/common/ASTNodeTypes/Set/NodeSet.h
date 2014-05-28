/*
 * NodeSet.h
 *
 *  Created on: May 28, 2014
 *      Author: cmaier
 */

#ifndef NODESET_H_
#define NODESET_H_

#include <vector>
#include <memory>

#include "../ASTNodeBase.h"
#include "../../ASTNodeTypes/Tuple/NodeTuple.h"

class NodeSet: public ASTNodeBase
{
  private:
    std::vector<std::shared_ptr<NodeTuple>> tuples_;

  public:
    NodeSet();
    virtual ~NodeSet();

    const std::vector<std::shared_ptr<NodeTuple>>& getTuples() const
    {
      return tuples_;
    }

    void addTuple(const std::shared_ptr<NodeTuple>& tuple)
    {
      tuples_.push_back(tuple);
    }
//    void setTuples(const std::vector<std::shared_ptr<NodeTuple> >& tuples)
//    {
//      tuples_ = tuples;
//    }

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      visitor->visit(this);

      std::for_each(std::begin(tuples_), std::end(tuples_),
          [&visitor](std::shared_ptr<NodeTuple> tuple)
          { tuple->accept(visitor);});
    }
};

#endif /* NODESET_H_ */
