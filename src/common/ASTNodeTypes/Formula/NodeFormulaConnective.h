/**
 * @file   NodeFormulaConnective.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for formula connectives
 */

#ifndef NODEFORMULACONNECTIVE_H_
#define NODEFORMULACONNECTIVE_H_

#include <string>
#include <stdexcept>

#include "../ASTNodeBase.h"

/**
 * Possible formula connectives
 */
enum class FormulaConnective
{
  And, Or, Implies, Unknown
};

/**
 * AST node class for formula connectives
 */
class NodeFormulaConnective: public ASTNodeBase<>
{
  private:
    /**
     * The formula connective
     */
    FormulaConnective formulaConnective_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeFormulaConnective();

    /**
     * Default dtor
     */
    virtual ~NodeFormulaConnective();

    /**
     * Parses the formula connective from the string representation
     * @param connString The connective as string
     */
    void fromString(const std::string& connString);

    /**
     * Stringifies the connective
     * @return The stringified version of the connective
     */
    std::string toString();

    /**
     * Getter for the formula connective
     * @return The formula connective
     */
    FormulaConnective getFormulaConnective() const
    {
      return formulaConnective_;
    }

    /**
     * Setter for the formula connective
     * @param formulaConnective The formula connective
     */
    void setFormulaConnective(FormulaConnective formulaConnective)
    {
      formulaConnective_ = formulaConnective;
    }
};

#endif /* NODEFORMULACONNECTIVE_H_ */
