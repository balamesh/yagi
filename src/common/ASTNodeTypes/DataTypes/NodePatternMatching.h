/*
 * NodePatternMatching.h
 *
 *  Created on: Jun 5, 2014
 *      Author: cmaier
 */

#ifndef NODEPATTERNMATCHING_H_
#define NODEPATTERNMATCHING_H_

#include "../ASTNodeBase.h"

class NodePatternMatching: public ASTNodeBase
{
  public:
    NodePatternMatching();
    virtual ~NodePatternMatching();

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      //TODO: implement this
      //visitor->visit(this);
    }
};

#endif /* NODEPATTERNMATCHING_H_ */
