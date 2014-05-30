/*
 * NodeFormulaConnective.h
 *
 *  Created on: May 30, 2014
 *      Author: cmaier
 */

#ifndef NODEFORMULACONNECTIVE_H_
#define NODEFORMULACONNECTIVE_H_

#include <string>
#include <stdexcept>

#include "../ASTNodeBase.h"

enum class FormulaConnective
{
  And, Or, Implies, Unknown
};

class NodeFormulaConnective: public ASTNodeBase
{
  private:
    FormulaConnective formularConnective_;

  public:
    NodeFormulaConnective();
    virtual ~NodeFormulaConnective();

    void fromString(const std::string& connString)
    {
      if (connString == "&&")
        formularConnective_ = FormulaConnective::And;
      else if (connString == "||")
        formularConnective_ = FormulaConnective::Or;
      else if (connString == "->")
        formularConnective_ = FormulaConnective::Implies;
      else
        throw std::runtime_error("Invalid formula connective string '" + connString + "'!");
    }

    FormulaConnective getFormularConnective() const
    {
      return formularConnective_;
    }

    void setFormularConnective(FormulaConnective formularConnective)
    {
      formularConnective_ = formularConnective;
    }

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      visitor->visit(this);
    }
};

#endif /* NODEFORMULACONNECTIVE_H_ */
