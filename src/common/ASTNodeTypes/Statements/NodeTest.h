/**
 * @file   NodeTest.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for YAGI test-statement
 */

#ifndef NODETEST_H_
#define NODETEST_H_

#include <memory>

#include "NodeStatementBase.h"
#include "../Formula/NodeFormulaBase.h"

/**
 * AST node class for YAGI test-statement
 */
class NodeTest: public NodeStatementBase
{
  private:

    /**
     * The formula to test
     */
    std::shared_ptr<NodeFormulaBase> formula_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeTest();

    /**
     * Default dtor
     */
    virtual ~NodeTest();

    /**
     * Getter for the formula to test
     * @return The formula to test
     */
    const std::shared_ptr<NodeFormulaBase>& getFormula() const
    {
      return formula_;
    }

    /**
     * Setter for the formula to test
     * @param formula The formula to test
     */
    void setFormula(const std::shared_ptr<NodeFormulaBase>& formula)
    {
      formula_ = formula;
    }
};

#endif /* NODETEST_H_ */
