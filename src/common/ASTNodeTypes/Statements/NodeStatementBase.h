/*
 * NodeStatementBase.h
 *
 *  Created on: Jun 4, 2014
 *      Author: cmaier
 */

#ifndef NODESTATEMENTBASE_H_
#define NODESTATEMENTBASE_H_

#include "../ASTNodeBase.h"

class NodeStatementBase: public ASTNodeBase<>
{
  public:
    NodeStatementBase();
    virtual ~NodeStatementBase();
};

#endif /* NODESTATEMENTBASE_H_ */
