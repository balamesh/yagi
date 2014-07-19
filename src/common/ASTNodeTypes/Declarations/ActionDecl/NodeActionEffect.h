/*
 * NodeActionEffect.h
 *
 *  Created on: May 23, 2014
 *      Author: cmaier
 */

#ifndef NODEACTIONEFFECT_H_
#define NODEACTIONEFFECT_H_

#include <memory>
#include <vector>
#include <algorithm>

#include "../../ASTNodeBase.h"
#include "../../Statements/NodeBlock.h"

class NodeActionEffect: public ASTNodeBase<>
{
  private:
    std::shared_ptr<NodeBlock> block_;
  public:
    DEFINE_VISITABLE()
    NodeActionEffect();
    virtual ~NodeActionEffect();

    const std::shared_ptr<NodeBlock>& getBlock() const
    {
      return block_;
    }

    void setBlock(const std::shared_ptr<NodeBlock>& block)
    {
      block_ = block;
    }
};

#endif /* NODEACTIONEFFECT_H_ */
