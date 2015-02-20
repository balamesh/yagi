/**
 * @file   NodePatternMatching.h
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * AST node for pattern matching.
 */

#ifndef NODEPATTERNMATCHING_H_
#define NODEPATTERNMATCHING_H_

#include "../ASTNodeBase.h"

/**
 * AST node class for pattern matching.
 */
class NodePatternMatching: public ASTNodeBase<>
{
  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodePatternMatching();

    /**
     * Default dtor
     */
    virtual ~NodePatternMatching();
};

#endif /* NODEPATTERNMATCHING_H_ */
