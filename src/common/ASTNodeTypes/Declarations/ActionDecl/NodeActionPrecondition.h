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
#include "../../Formula/NodeFormula.h"

class NodeActionPrecondition: public ASTNodeBase
{
  private:
    std::shared_ptr<NodeFormula> formula_;
  public:
    NodeActionPrecondition();
    virtual ~NodeActionPrecondition();

    const std::shared_ptr<NodeFormula>& getFormula() const
    {
      return formula_;
    }

    void setFormula(const std::shared_ptr<NodeFormula>& formula)
    {
      formula_ = formula;
    }

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      //TODO: implement this
      //visitor->visit(this);
    }
};

#endif /* NODEACTIONPRECONDITION_H_ */
