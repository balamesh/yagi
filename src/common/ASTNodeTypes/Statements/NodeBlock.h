/*
 * NodeBlock.h
 *
 *  Created on: Jun 4, 2014
 *      Author: cmaier
 */

#ifndef NODEBLOCK_H_
#define NODEBLOCK_H_

#include <vector>
#include <memory>
#include <algorithm>

#include "../ASTNodeBase.h"
#include "NodeStatementBase.h"

class NodeBlock: public ASTNodeBase<>
{
  private:
    std::vector<std::shared_ptr<NodeStatementBase>> statements_;

  public:
    DEFINE_VISITABLE()
    NodeBlock();
    virtual ~NodeBlock();

    const std::vector<std::shared_ptr<NodeStatementBase>>& getStatements() const
    {
      return statements_;
    }

    void addStatement(const std::shared_ptr<NodeStatementBase>& statement)
    {
      statements_.push_back(statement);
    }

//    virtual void accept(ASTNodeVisitorBase* visitor) override
//    {
//      std::for_each(std::begin(statements_), std::end(statements_),
//          [&visitor](std::shared_ptr<NodeStatementBase> stmt)
//          { stmt->accept(visitor);});
//
//      visitor->visit(this);
//    }
};

#endif /* NODEBLOCK_H_ */
