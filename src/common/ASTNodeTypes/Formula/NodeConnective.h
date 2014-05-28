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

enum class FormulaConnective
{
  And, Or, Implies, Eq, Neq, Ge, Gt, Le, Lt, Unknown
};

class NodeConnective: public ASTNodeBase
{
  private:
    FormulaConnective connective_;

  public:
    NodeConnective();
    virtual ~NodeConnective();

    FormulaConnective getConnective() const
    {
      return connective_;
    }

    void setConnective(FormulaConnective connective)
    {
      connective_ = connective;
    }


    void fromString(const std::string& connString)
    {
      if (connString == "&&")
        connective_ = FormulaConnective::And;
      else if (connString == "||")
        connective_ = FormulaConnective::Or;
      else if (connString == "->")
        connective_ = FormulaConnective::Implies;
      else if (connString == "==")
        connective_ = FormulaConnective::Eq;
      else if (connString == "!=")
        connective_ = FormulaConnective::Neq;
      else if (connString == "<=")
        connective_ = FormulaConnective::Le;
      else if (connString == ">=")
        connective_ = FormulaConnective::Ge;
      else if (connString == "<")
        connective_ = FormulaConnective::Lt;
      else if (connString == ">")
        connective_ = FormulaConnective::Gt;
      else
        throw std::runtime_error("Invalid connective string '" + connString + "'!");
    }

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      //TODO: implement this
      //visitor->visit(this);
    }
};

#endif /* NODECONNECTIVE_H_ */
