/**
 * @file   NodeFormulaBase.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for base formula
 */

#ifndef NODEFORMULABASE_H_
#define NODEFORMULABASE_H_

#include "../ASTNodeBase.h"

/**
 * AST node class for base formula
 */
class NodeFormulaBase: public ASTNodeBase<>
{
  public:
    /**
     * Default ctor
     */
    NodeFormulaBase();

    /**
     * Default dtor
     */
    virtual ~NodeFormulaBase();
};

#endif /* NODEFORMULABASE_H_ */
