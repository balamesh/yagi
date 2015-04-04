/**
 * @file   NodeWhileLoop.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for YAGI while-loops
 */

#ifndef NODEWHILELOOP_H_
#define NODEWHILELOOP_H_

#include "NodeStatementBase.h"

#include "../Formula/NodeFormulaBase.h"
#include "NodeBlock.h"

/**
 * AST node class for YAGI while-loops
 */
class NodeWhileLoop: public NodeStatementBase
{
  private:
    /**
     * The while-condition formula
     */
    std::shared_ptr<NodeFormulaBase> formula_;

    /**
     * The while-block
     */
    std::shared_ptr<NodeBlock> block_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeWhileLoop();

    /**
     * Default dtor
     */
    virtual ~NodeWhileLoop();

    /**
     * Getter for the while-block
     * @return The while-block
     */
    const std::shared_ptr<NodeBlock>& getBlock() const
    {
      return block_;
    }

    /**
     * Setter for the while-block
     * @param block The while-block
     */
    void setBlock(const std::shared_ptr<NodeBlock>& block)
    {
      block_ = block;
    }

    /**
     * Getter for the while-condition
     * @return The while-condition formula
     */
    const std::shared_ptr<NodeFormulaBase>& getFormula() const
    {
      return formula_;
    }

    /**
     * Setter for the while-condition
     * @param formula The while-condition formula
     */
    void setFormula(const std::shared_ptr<NodeFormulaBase>& formula)
    {
      formula_ = formula;
    }
};

#endif /* NODEWHILELOOP_H_ */
