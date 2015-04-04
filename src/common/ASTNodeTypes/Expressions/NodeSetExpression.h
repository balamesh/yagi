/**
 * @file   NodeSetExpression.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for set expressions
 */

#ifndef NODESETEXPRESSION_H_
#define NODESETEXPRESSION_H_

#include "../ASTNodeBase.h"
#include "NodeExpressionOperator.h"
#include "../../ASTNodeTypes/Identifier/NodeID.h"
#include "../../ASTNodeTypes/Set/NodeSet.h"

#include <memory>

/**
 * AST node class for set expressions
 */
class NodeSetExpression: public ASTNodeBase<>
{
  private:
    /**
     * Expression operator
     */
    std::shared_ptr<NodeExpressionOperator> operator_;

    /**
     * Left-hand side of the expression
     */
    std::shared_ptr<ASTNodeBase<>> lhs_;

    /**
     * Right-hand side of the expression
     */
    std::shared_ptr<ASTNodeBase<>> rhs_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeSetExpression();

    /**
     * Default dtor
     */
    virtual ~NodeSetExpression();

    /**
     * Checks whether or not the passed value is a valid expression value
     * @param valueToAssign The value to check
     * @return True if type is valid, false otherwise
     */
    static bool isPassedTypeValid(const std::shared_ptr<ASTNodeBase<>>& valueToAssign);

    /**
     * Getter for the lhs of the expression
     * @return The lhs of the expression
     */
    const std::shared_ptr<ASTNodeBase<>>& getLhs() const
    {
      return lhs_;
    }

    /**
     * Setter for the lhs of the expression
     * @param lhs The lhs of the expression
     */
    void setLhs(const std::shared_ptr<ASTNodeBase<>>& lhs)
    {
      if (isPassedTypeValid(lhs))
        this->lhs_ = lhs;
      else
        throw std::runtime_error("Invalid Type passed to SetExpression (lhs)!");
    }

    /**
     * Getter for the expression operator
     * @return The expression operator
     */
    const std::shared_ptr<NodeExpressionOperator>& getOperator() const
    {
      return operator_;
    }

    /**
     * Setter for the expression operator
     * @param _operator The operator to be set
     */
    void setOperator(const std::shared_ptr<NodeExpressionOperator>& _operator)
    {
      operator_ = _operator;
    }

    /**
     * Getter for the rhs of the expression
     * @return The rhs of the expression
     */
    const std::shared_ptr<ASTNodeBase<>>& getRhs() const
    {
      return rhs_;
    }

    /**
     * Setter for the rhs of the expression
     * @param rhs The rhs of the expression
     */
    void setRhs(const std::shared_ptr<ASTNodeBase<>>& rhs)
    {
      if (isPassedTypeValid(rhs))
        this->rhs_ = rhs;
      else
        throw std::runtime_error("Invalid Type passed to SetExpression (rhs)!");
    }
};

#endif /* NODESETEXPRESSION_H_ */
