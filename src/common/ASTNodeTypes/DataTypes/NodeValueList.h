/**
 * @file   NodeValueList.h
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * AST node for value lists.
 */

#ifndef NODEVALUELIST_H_
#define NODEVALUELIST_H_

#include <memory>
#include <vector>

#include "../ASTNodeBase.h"
#include "../Variables/NodeVariable.h"
#include "NodeString.h"

/**
 * AST node class for value lists
 */
class NodeValueList: public ASTNodeBase<>
{
  private:
    /**
     * Values in the value list
     */
    std::vector<std::shared_ptr<ASTNodeBase<>>>values_;

    /**
     * Checks whether or not a passed Node is a valid ValueNode
     * @param valueToAdd The node to check
     * @return True if node type is valid, false otherwise
     */
    bool isPassedTypeValid(const std::shared_ptr<ASTNodeBase<>>& valueToAdd);

    public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeValueList();

    /**
     * Default dtor
     */
    virtual ~NodeValueList();

    /**
     * Add value to value list
     * @param value The value node
     */
    void addValue(const std::shared_ptr<ASTNodeBase<>>& value);

    /**
     * Getter for value nodes
     * @return The value nodes
     */
    const std::vector<std::shared_ptr<ASTNodeBase<> > >& getValues() const
    {
      return values_;
    }
  };

#endif /* NODEVALUELIST_H_ */
