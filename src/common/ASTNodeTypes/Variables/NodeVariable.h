/**
 * @file   NodeVariable.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for YAGI variables
 */

#ifndef NODEVARIABLE_H_
#define NODEVARIABLE_H_

#include "../../ASTNodeTypes/ASTNodeBase.h"
#include <string>

/**
 * AST node class for YAGI variables
 */
class NodeVariable: public ASTNodeBase<>
{
  private:

    /**
     * The name of the variable
     */
    std::string varName_;
  public:
    DEFINE_VISITABLE()

    /**
     * Ctor
     */
    NodeVariable(const std::string& varName);

    /**
     * Default ctor
     */
    NodeVariable();

    /**
     * Default dtor
     */
    virtual ~NodeVariable();

    /**
     * Getter for the variable name
     * @return The name of the variable
     */
    const std::string& getVarName() const
    {
      return varName_;
    }

    /**
     * Setter for the variable name
     * @param varName The name of the variable
     */
    void setVarName(const std::string& varName)
    {
      varName_ = varName;
    }
};

#endif /* NODEVARIABLE_H_ */
