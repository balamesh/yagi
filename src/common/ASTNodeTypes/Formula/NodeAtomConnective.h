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

    void fromString(const std::string& connString);
    std::string toString();
};

#endif /* NODECONNECTIVE_H_ */
