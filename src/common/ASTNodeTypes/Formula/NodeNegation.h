/*
 * NodeNegation.h
 *
 *  Created on: May 30, 2014
 *      Author: cmaier
 */

#ifndef NODENEGATION_H_
#define NODENEGATION_H_

#include <memory>

#include "NodeFormulaBase.h"

class NodeNegation: public NodeFormulaBase
{
  private:
    std::shared_ptr<NodeFormulaBase> formula_;

  public:
    NodeNegation();
    virtual ~NodeNegation();

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

#endif /* NODENEGATION_H_ */
