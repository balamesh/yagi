/**
 * @file   NodeIncompleteKnowledge.h
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * AST node for incomplete knowledge.
 */

#ifndef NODEINCOMPLETEKNOWLEDGE_H_
#define NODEINCOMPLETEKNOWLEDGE_H_

#include "../ASTNodeBase.h"

/**
 * AST node class for incomplete knowledge.
 */
class NodeIncompleteKnowledge: public ASTNodeBase<>
{
  public:
    DEFINE_VISITABLE()
    /**
     * Default ctor
     */
    NodeIncompleteKnowledge();

    /**
     * Default dtor
     */
    virtual ~NodeIncompleteKnowledge();
};

#endif /* NODEINCOMPLETEKNOWLEDGE_H_ */
