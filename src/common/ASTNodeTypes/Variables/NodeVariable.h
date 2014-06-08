/*
 * NodeVariable.h
 *
 *  Created on: May 23, 2014
 *      Author: cmaier
 */

#ifndef NODEVARIABLE_H_
#define NODEVARIABLE_H_

#include "../../ASTNodeTypes/ASTNodeBase.h"
#include <string>

class NodeVariable: public ASTNodeBase<>
{
  private:
    std::string varName_;
  public:
    DEFINE_VISITABLE()
    NodeVariable(std::string varName) :
        varName_(varName)
    {
    }
    NodeVariable();
    virtual ~NodeVariable();

    const std::string& getVarName() const
    {
      return varName_;
    }

    void setVarName(const std::string& varName)
    {
      varName_ = varName;
    }

//    virtual void accept(ASTNodeVisitorBase* visitor) override
//    {
//      visitor->visit(this);
//    }

};

#endif /* NODEVARIABLE_H_ */
