/*
 * NodeFormulaBase.h
 *
 *  Created on: May 28, 2014
 *      Author: cmaier
 */

#ifndef NODEFORMULABASE_H_
#define NODEFORMULABASE_H_

#include "../ASTNodeBase.h"

class NodeFormulaBase: public ASTNodeBase
{
  public:
    NodeFormulaBase();
    virtual ~NodeFormulaBase();
};

#endif /* NODEFORMULABASE_H_ */
