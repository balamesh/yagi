/*
 * NodeSearch.h
 *
 *  Created on: Jun 5, 2014
 *      Author: cmaier
 */

#ifndef NODESEARCH_H_
#define NODESEARCH_H_

#include "NodeStatementBase.h"
#include "NodeBlock.h"

class NodeSearch: public NodeStatementBase
{
  private:
    std::shared_ptr<NodeBlock> block_;

  public:
    DEFINE_VISITABLE()
    NodeSearch();
    virtual ~NodeSearch();

    const std::shared_ptr<NodeBlock>& getBlock() const
    {
      return block_;
    }

    void setBlock(const std::shared_ptr<NodeBlock>& block)
    {
      block_ = block;
    }
};

#endif /* NODESEARCH_H_ */
