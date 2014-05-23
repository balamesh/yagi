#ifndef NODEPROGRAM_H
#define NODEPROGRAM_H

#include<vector>
#include<memory>
#include <algorithm>

#include "../ASTNodeBase.h"


class NodeProgram: public ASTNodeBase
{
  private:
    std::vector<std::shared_ptr<ASTNodeBase>> program;

  public:
    void addStatementToProgram(std::shared_ptr<ASTNodeBase> statement)
    {
      program.push_back(statement);
    }

    NodeProgram();
    virtual ~NodeProgram();

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      std::for_each(program.begin(), program.end(),
          [&visitor](std::shared_ptr<ASTNodeBase> stmt)
          {
            stmt->accept(visitor);
          });

      visitor->visit(this);
    }

    const std::vector<std::shared_ptr<ASTNodeBase> >& getProgram() const
    {
      return program;
    }
};

#endif // NODEPROGRAM_H
