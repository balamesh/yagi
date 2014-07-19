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
    std::vector<std::shared_ptr<ASTNodeBase<>>>values_;

    bool isPassedTypeValid(const std::shared_ptr<ASTNodeBase<>>& valueToAdd);

    public:
    DEFINE_VISITABLE()
    NodeValueList();
    virtual ~NodeValueList();

    void addValue(const std::shared_ptr<ASTNodeBase<>>& value);

    const std::vector<std::shared_ptr<ASTNodeBase<> > >& getValues() const
    {
      return values_;
    }
  };

#endif /* NODEVALUELIST_H_ */
