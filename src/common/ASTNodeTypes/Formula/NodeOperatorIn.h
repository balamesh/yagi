/**
 * @file   NodeOperatorIn.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for "tuple-in-set" formulas
 */

#ifndef NODEOPERATORIN_H_
#define NODEOPERATORIN_H_

#include <memory>

#include "../Tuple/NodeTuple.h"
#include "../Expressions/NodeSetExpression.h"

#include "NodeFormulaBase.h"

/**
 * AST node class for "tuple-in-set" formulas
 */
class NodeOperatorIn: public NodeFormulaBase
{
  private:

    /**
     * The tuple to check
     */
    std::shared_ptr<NodeTuple> tuple_;

    /**
     * The set to check
     */
    std::shared_ptr<ASTNodeBase<>> setExpr_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeOperatorIn();

    /**
     * Default dtor
     */
    virtual ~NodeOperatorIn();

    /**
     * Getter for the set to check
     * @return The set to check
     */
    const std::shared_ptr<ASTNodeBase<>>& getSetExpr() const
    {
      return setExpr_;
    }

    /**
     * Setter for the set to check
     * @param setExpr The set to check
     */
    void setSetExpr(const std::shared_ptr<ASTNodeBase<>>& setExpr)
    {
      setExpr_ = setExpr;
    }

    /**
     * Getter for the tuple to check
     * @return The tuple to check
     */
    const std::shared_ptr<NodeTuple>& getTuple() const
    {
      return tuple_;
    }

    /**
     * Setter for the tuple to check
     * @param tuple The tuple to check
     */
    void setTuple(const std::shared_ptr<NodeTuple>& tuple)
    {
      tuple_ = tuple;
    }
};

#endif /* NODEOPERATORIN_H_ */
