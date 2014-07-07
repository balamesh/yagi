/*
 * NodeValueList.h
 *
 *  Created on: Jun 5, 2014
 *      Author: cmaier
 */

#ifndef NODEVALUELIST_H_
#define NODEVALUELIST_H_

#include <memory>
#include <vector>

#include "../ASTNodeBase.h"
#include "../Variables/NodeVariable.h"
#include "NodeString.h"

class NodeValueList: public ASTNodeBase<>
{
  private:
    std::vector<std::shared_ptr<ASTNodeBase<>>> values_;

    bool isPassedTypeValid(const std::shared_ptr<ASTNodeBase<>>& valueToAdd);
  public:
    DEFINE_VISITABLE()
    NodeValueList();
    virtual ~NodeValueList();

    void addValue(const std::shared_ptr<ASTNodeBase<>>& value)
    {
      if (isPassedTypeValid(value))
        values_.push_back(value);
      else
        throw std::runtime_error("Invalid Type passed to ValueList!");
    }
};

#endif /* NODEVALUELIST_H_ */
