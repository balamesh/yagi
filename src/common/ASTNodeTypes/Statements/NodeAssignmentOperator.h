/**
 * @file   NodeAssignmentOperator.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for assignment operators
 */

#ifndef NODEASSIGNMENTOPERATOR_H_
#define NODEASSIGNMENTOPERATOR_H_

#include <string>
#include <stdexcept>

#include "../ASTNodeBase.h"

/**
 * The types of assignment operators
 */
enum class AssignmentOperator
{
  Assign, AddAssign, RemoveAssign, Unknown
};

/**
 * AST node class for assignment operators
 */
class NodeAssignmentOperator: public ASTNodeBase<>
{
  private:
    /**
     * The assignment operator
     */
    AssignmentOperator operator_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeAssignmentOperator();

    /**
     * Default dtor
     */
    virtual ~NodeAssignmentOperator();

    /**
     * Getter for the assignment operator
     * @return The assignment operator
     */
    AssignmentOperator getOperator() const
    {
      return operator_;
    }

    /**
     * Setter for the assignment operator
     * @param _operator The assignment operator
     */
    void setOperator(AssignmentOperator _operator)
    {
      operator_ = _operator;
    }

    /**
     * Stringifies the assignment operator
     * @return Stringified version of the operator
     */
    std::string toString();

    /**
     * Parses the operator from its string representation
     * @param opString The operator string
     */
    void fromString(const std::string& opString);
};

#endif /* NODEASSIGNMENTOPERATOR_H_ */
