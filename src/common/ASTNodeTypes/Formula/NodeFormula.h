/*
 * NodeFormula.h
 *
 *  Created on: May 23, 2014
 *      Author: cmaier
 */

#ifndef NODEFORMULA_H_
#define NODEFORMULA_H_

#include "../ASTNodeBase.h"

class NodeFormula: public ASTNodeBase
{
  public:
    NodeFormula();
    virtual ~NodeFormula();

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      //TODO: implement this
      //visitor->visit(this);
    }
};

#endif /* NODEFORMULA_H_ */
