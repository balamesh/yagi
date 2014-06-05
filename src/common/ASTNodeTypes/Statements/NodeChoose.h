/*
 * NodeChoose.h
 *
 *  Created on: Jun 5, 2014
 *      Author: cmaier
 */

#ifndef NODECHOOSE_H_
#define NODECHOOSE_H_

#include <memory>
#include <vector>

#include "NodeStatementBase.h"
#include "NodeBlock.h"

class NodeChoose: public NodeStatementBase
{
  private:
    std::vector<std::shared_ptr<NodeBlock>> blocks_;

  public:
    NodeChoose();
    virtual ~NodeChoose();

    const std::vector<std::shared_ptr<NodeBlock> >& getBlocks() const
    {
      return blocks_;
    }

    void addBlock(const std::shared_ptr<NodeBlock>& block)
    {
      blocks_.push_back(block);
    }

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      //TODO: implement this
      //visitor->visit(this);
    }
};

#endif /* NODECHOOSE_H_ */
