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

class NodeSet: public ASTNodeBase<>
{
  private:
    std::vector<std::shared_ptr<NodeTuple>> tuples_;

  public:
    DEFINE_VISITABLE()
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
};

#endif /* NODESET_H_ */
