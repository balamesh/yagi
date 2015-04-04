/**
 * @file   NodeVarList.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for YAGI variable lists
 */

#ifndef NODEVARLIST_H_
#define NODEVARLIST_H_

#include <vector>
#include <memory>
#include <algorithm>

#include "../../ASTNodeTypes/ASTNodeBase.h"
#include "../../ASTNodeTypes/Variables/NodeVariable.h"

/**
 * AST node class for YAGI variable lists
 */
class NodeVarList: public ASTNodeBase<>
{
  private:
    /**
     * List of variables
     */
    std::vector<std::shared_ptr<NodeVariable>> variables_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeVarList();

    /**
     * Default dtor
     */
    virtual ~NodeVarList();

    /**
     * Getter for the list of variables
     * @return The list of variables
     */
    const std::vector<std::shared_ptr<NodeVariable> >& getVariables() const
    {
      return variables_;
    }

    /**
     * Adds a variable to the list
     * @param variable The variable to add
     */
    void addVariable(std::shared_ptr<NodeVariable> variable)
    {
      variables_.push_back(variable);
    }
};

#endif /* NODEVARLIST_H_ */
