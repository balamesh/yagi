/*
 * NodeTest.h
 *
 *  Created on: Jun 5, 2014
 *      Author: cmaier
 */

#ifndef NODETEST_H_
#define NODETEST_H_

#include <memory>

#include "NodeStatementBase.h"
#include "../Formula/NodeFormulaBase.h"

class NodeTest: public NodeStatementBase
{
  private:
    std::shared_ptr<NodeFormulaBase> formula_;

  public:
    NodeTest();
    virtual ~NodeTest();

    const std::shared_ptr<NodeFormulaBase>& getFormula() const
    {
      return formula_;
    }

    void setFormula(const std::shared_ptr<NodeFormulaBase>& formula)
    {
      formula_ = formula;
    }

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      formula_->accept(visitor);

      visitor->visit(this);
    }
};

#endif /* NODETEST_H_ */
