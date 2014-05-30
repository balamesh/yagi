/*
 * NodeActionPrecondition.h
 *
 *  Created on: May 23, 2014
 *      Author: cmaier
 */

#ifndef NODEACTIONPRECONDITION_H_
#define NODEACTIONPRECONDITION_H_

#include <memory>

#include "../../ASTNodeBase.h"
#include "../../Formula/NodeFormulaBase.h"

class NodeActionPrecondition: public ASTNodeBase
{
  private:
    std::shared_ptr<NodeFormulaBase> formula_;
  public:
    NodeActionPrecondition(const std::shared_ptr<NodeFormulaBase>& formula) :
        formula_(formula)
    {
    }
    NodeActionPrecondition();
    virtual ~NodeActionPrecondition();

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
      visitor->visit(this);

      formula_->accept(visitor);
    }
};

#endif /* NODEACTIONPRECONDITION_H_ */
