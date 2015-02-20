/**
 * @file   NodeActionEffect.h
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * AST node for action effects.
 */

#ifndef NODEACTIONEFFECT_H_
#define NODEACTIONEFFECT_H_

#include <memory>
#include <vector>
#include <algorithm>

#include "../../ASTNodeBase.h"
#include "../../Statements/NodeBlock.h"

/**
 * AST node class for action effects
 */
class NodeActionEffect: public ASTNodeBase<>
{
  private:
    /**
     * The action effect block
     */
    std::shared_ptr<NodeBlock> block_;
  public:
    DEFINE_VISITABLE()
    /**
     * Default ctor
     */
    NodeActionEffect();

    /**
     * Default dtor
     */
    virtual ~NodeActionEffect();

    /**
     * Getter for the effect block
     * @return The effect block node
     */
    const std::shared_ptr<NodeBlock>& getBlock() const
    {
      return block_;
    }

    /**
     * Setter for the effect block
     * @param block The effect block node
     */
    void setBlock(const std::shared_ptr<NodeBlock>& block)
    {
      block_ = block;
    }
};

#endif /* NODEACTIONEFFECT_H_ */
