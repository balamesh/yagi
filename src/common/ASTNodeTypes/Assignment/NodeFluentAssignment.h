/*
 * NodeFluentAssignment.h
 *
 *  Created on: May 27, 2014
 *      Author: cmaier
 */

#ifndef NODEFLUENTASSIGNMENT_H_
#define NODEFLUENTASSIGNMENT_H_

#include "../../ASTNodeTypes/ASTNodeBase.h"
#include <memory>

class NodeFluentAssignment: public ASTNodeBase
{
  private:
    std::shared_ptr<NodeID> fluentName_;

  public:
    NodeFluentAssignment();
    virtual ~NodeFluentAssignment();
};

#endif /* NODEFLUENTASSIGNMENT_H_ */
