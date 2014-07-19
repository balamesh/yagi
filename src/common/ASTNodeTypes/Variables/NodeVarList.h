/*
 * NodeVarList.h
 *
 *  Created on: May 23, 2014
 *      Author: cmaier
 */

#ifndef NODEVARLIST_H_
#define NODEVARLIST_H_

#include <vector>
#include <memory>
#include <algorithm>

#include "../../ASTNodeTypes/ASTNodeBase.h"
#include "../../ASTNodeTypes/Variables/NodeVariable.h"

class NodeVarList: public ASTNodeBase<>
{
  private:
    std::vector<std::shared_ptr<NodeVariable>> variables_;

  public:
    DEFINE_VISITABLE()
    NodeVarList();
    virtual ~NodeVarList();

    const std::vector<std::shared_ptr<NodeVariable> >& getVariables() const
    {
      return variables_;
    }

    void addVariable(std::shared_ptr<NodeVariable> variable)
    {
      variables_.push_back(variable);
    }
};

#endif /* NODEVARLIST_H_ */
