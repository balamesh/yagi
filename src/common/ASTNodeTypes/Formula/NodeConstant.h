/*
 * NodeConstant.h
 *
 *  Created on: May 28, 2014
 *      Author: cmaier
 */

#ifndef NODECONSTANT_H_
#define NODECONSTANT_H_

#include "NodeFormulaBase.h"

class NodeConstant: public NodeFormulaBase
{
  private:
    bool truthValue_;
  public:
    NodeConstant();
    virtual ~NodeConstant();

    bool getTruthValue() const
    {
      return truthValue_;
    }

    void setTruthValue(bool truthValue)
    {
      truthValue_ = truthValue;
    }

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      //TODO: implement this!
      //visitor->visit(this);
    }
};

#endif /* NODECONSTANT_H_ */
