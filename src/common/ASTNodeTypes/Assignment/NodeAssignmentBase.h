/*
 * NodeAssignmentBase.h
 *
 *  Created on: May 30, 2014
 *      Author: cmaier
 */

#ifndef NODEASSIGNMENTBASE_H_
#define NODEASSIGNMENTBASE_H_

#include "../ASTNodeBase.h"

class NodeAssignmentBase: public ASTNodeBase<>
{
  public:
    NodeAssignmentBase();
    virtual ~NodeAssignmentBase();
};

#endif /* NODEASSIGNMENTBASE_H_ */
