/*
 * NodeIncompleteKnowledge.h
 *
 *  Created on: Jul 7, 2014
 *      Author: cmaier
 */

#ifndef NODEINCOMPLETEKNOWLEDGE_H_
#define NODEINCOMPLETEKNOWLEDGE_H_

#include "../ASTNodeBase.h"

class NodeIncompleteKnowledge: public ASTNodeBase<>
{
  public:
    DEFINE_VISITABLE()
    NodeIncompleteKnowledge();
    virtual ~NodeIncompleteKnowledge();
};

#endif /* NODEINCOMPLETEKNOWLEDGE_H_ */
