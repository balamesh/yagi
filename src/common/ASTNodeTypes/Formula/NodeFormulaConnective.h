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

class NodeFormulaConnective: public ASTNodeBase<>
{
  private:
    FormulaConnective formulaConnective_;

  public:
    DEFINE_VISITABLE()
    NodeFormulaConnective();
    virtual ~NodeFormulaConnective();

    void fromString(const std::string& connString);
    std::string toString();

    FormulaConnective getFormulaConnective() const
    {
      return formulaConnective_;
    }

    void setFormulaConnective(FormulaConnective formulaConnective)
    {
      formulaConnective_ = formulaConnective;
    }
};

#endif /* NODEFORMULACONNECTIVE_H_ */
