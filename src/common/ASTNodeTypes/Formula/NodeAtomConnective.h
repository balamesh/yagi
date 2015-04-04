/**
 * @file   NodeAtomConnective.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for atom connectives
 */

#ifndef NODECONNECTIVE_H_
#define NODECONNECTIVE_H_

#include <string>
#include <stdexcept>

#include "../ASTNodeBase.h"

/**
 * Valid atom connectives
 */
enum class AtomConnective
{
  Eq, Neq, Ge, Gt, Le, Lt, Unknown
};

/**
 * AST node class for atom connectives
 */
class NodeAtomConnective: public ASTNodeBase<>
{
  private:
    /**
     * The atom connective
     */
    AtomConnective atomConnective_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeAtomConnective();

    /**
     * Default dtor
     */
    virtual ~NodeAtomConnective();

    /**
     * Getter for the atom connective
     * @return The atom connective
     */
    AtomConnective getAtomConnective() const
    {
      return atomConnective_;
    }

    /**
     * Setter for the atom connective
     * @param connective The atom connective
     */
    void setAtomConnective(AtomConnective connective)
    {
      atomConnective_ = connective;
    }

    /**
     * Set atom connective from string symbol
     * @param connString The string symbol of the connective
     */
    void fromString(const std::string& connString);

    /**
     * Stringifies the connective
     * @return The strigifies connective
     */
    std::string toString();
};

#endif /* NODECONNECTIVE_H_ */
