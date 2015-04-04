/**
 * @file   NodeNegation.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for formula negations
 */

#ifndef NODENEGATION_H_
#define NODENEGATION_H_

#include <memory>

#include "NodeFormulaBase.h"

/**
 * AST node class for formula negations
 */
class NodeNegation: public NodeFormulaBase
{
  private:
    /**
     * The formula to be negated
     */
    std::shared_ptr<NodeFormulaBase> formula_;

  public:
    DEFINE_VISITABLE()
    /**
     * Default ctor
     */
    NodeNegation();

    /**
     * Default dtor
     */
    virtual ~NodeNegation();

    /**
     * Getter for the formula to be negated
     * @return The formula
     */
    const std::shared_ptr<NodeFormulaBase>& getFormula() const
    {
      return formula_;
    }

    /**
     * Setter for the formula to be negated
     * @param formula The formula
     */
    void setFormula(const std::shared_ptr<NodeFormulaBase>& formula)
    {
      formula_ = formula;
    }
};

#endif /* NODENEGATION_H_ */
