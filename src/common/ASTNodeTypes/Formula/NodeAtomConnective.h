/*
 * NodeConnective.h
 *
 *  Created on: May 28, 2014
 *      Author: cmaier
 */

#ifndef NODECONNECTIVE_H_
#define NODECONNECTIVE_H_

#include <string>
#include <stdexcept>

#include "../ASTNodeBase.h"

enum class AtomConnective
{
    Eq, Neq, Ge, Gt, Le, Lt, Unknown
};

class NodeAtomConnective: public ASTNodeBase<>
{
  private:
    AtomConnective atomConnective_;

  public:
    DEFINE_VISITABLE()
    NodeAtomConnective();
    virtual ~NodeAtomConnective();

    AtomConnective getAtomConnective() const
    {
      return atomConnective_;
    }

    void setAtomConnective(AtomConnective connective)
    {
      atomConnective_ = connective;
    }


    void fromString(const std::string& connString)
    {
      if (connString == "==")
        atomConnective_ = AtomConnective::Eq;
      else if (connString == "!=")
        atomConnective_ = AtomConnective::Neq;
      else if (connString == "<=")
        atomConnective_ = AtomConnective::Le;
      else if (connString == ">=")
        atomConnective_ = AtomConnective::Ge;
      else if (connString == "<")
        atomConnective_ = AtomConnective::Lt;
      else if (connString == ">")
        atomConnective_ = AtomConnective::Gt;
      else
        throw std::runtime_error("Invalid atom connective string '" + connString + "'!");
    }

//    virtual void accept(ASTNodeVisitorBase* visitor) override
//    {
//      visitor->visit(this);
//    }
};

#endif /* NODECONNECTIVE_H_ */
