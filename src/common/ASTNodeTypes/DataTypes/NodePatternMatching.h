/*
 * NodePatternMatching.h
 *
 *  Created on: Jun 5, 2014
 *      Author: cmaier
 */

#ifndef NODEPATTERNMATCHING_H_
#define NODEPATTERNMATCHING_H_

#include "../ASTNodeBase.h"

class NodePatternMatching: public ASTNodeBase<>
{
  public:
    DEFINE_VISITABLE()
    NodePatternMatching();
    virtual ~NodePatternMatching();
};

#endif /* NODEPATTERNMATCHING_H_ */
