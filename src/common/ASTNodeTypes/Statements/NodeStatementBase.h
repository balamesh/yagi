/**
 * @file   NodeStatementBase.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for basic YAGI statement
 */

#ifndef NODESTATEMENTBASE_H_
#define NODESTATEMENTBASE_H_

#include "../ASTNodeBase.h"

/**
 * AST node class for basic YAGI statement
 */
class NodeStatementBase: public ASTNodeBase<>
{
  public:
    /**
     * Default ctor
     */
    NodeStatementBase();

    /**
     * Default dtor
     */
    virtual ~NodeStatementBase();
};

#endif /* NODESTATEMENTBASE_H_ */
