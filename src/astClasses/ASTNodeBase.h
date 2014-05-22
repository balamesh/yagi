/*
 * ASTNodeBase.h
 *
 *  Created on: Apr 24, 2014
 *      Author: cmaier
 */

#ifndef ASTNODEBASE_H_
#define ASTNODEBASE_H_

#include "../astVisitors/ASTNodeVisitorBase.h"

class ASTNodeBase
{
  public:
    ASTNodeBase();
    virtual ~ASTNodeBase();

    virtual void accept(ASTNodeVisitorBase* visitor) = 0;
};

#endif /* ASTNODEBASE_H_ */
