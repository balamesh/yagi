/*
 * NodeConstant.h
 *
 *  Created on: May 28, 2014
 *      Author: cmaier
 */

#ifndef NODECONSTANT_H_
#define NODECONSTANT_H_

#include <string>
#include <stdexcept>

#include "NodeFormulaBase.h"

class NodeConstant: public NodeFormulaBase
{
  private:
    bool truthValue_;
  public:
    DEFINE_VISITABLE()
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

    void fromString(const std::string& truthVal)
    {
      if (truthVal == "true")
        truthValue_ = true;
      else if (truthVal == "false")
        truthValue_ = false;
      else
        throw std::runtime_error("Invalid atom connective string '" + truthVal + "'!");
    }

//    virtual void accept(ASTNodeVisitorBase* visitor) override
//    {
//      visitor->visit(this);
//    }
};

#endif /* NODECONSTANT_H_ */
