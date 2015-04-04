/**
 * @file   NodeSearch.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for a YAGI search statement
 */

#ifndef NODESEARCH_H_
#define NODESEARCH_H_

#include "NodeStatementBase.h"
#include "NodeBlock.h"

/**
 * AST node class for a YAGI search statement
 */
class NodeSearch: public NodeStatementBase
{
  private:
    /**
     * The block that should be searched over
     */
    std::shared_ptr<NodeBlock> block_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeSearch();

    /**
     * Default dtor
     */
    virtual ~NodeSearch();

    /**
     * Getter for the search-block
     * @return The search-block
     */
    const std::shared_ptr<NodeBlock>& getBlock() const
    {
      return block_;
    }

    /**
     * Setter for the search-block
     * @param block The search-block
     */
    void setBlock(const std::shared_ptr<NodeBlock>& block)
    {
      block_ = block;
    }
};

#endif /* NODESEARCH_H_ */
