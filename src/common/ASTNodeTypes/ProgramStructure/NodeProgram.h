#ifndef NODEPROGRAM_H
#define NODEPROGRAM_H

#include<vector>
#include<memory>

#include "../ASTNodeBase.h"

class NodeProgram: public ASTNodeBase<>
{
  private:
    std::vector<std::shared_ptr<ASTNodeBase<>>>program;

    public:
    NodeProgram();
    virtual ~NodeProgram();

    DEFINE_VISITABLE()
    void addStatementToProgram(std::shared_ptr<ASTNodeBase<>> statement)
    {
      program.insert(std::begin(program), statement);
    }

    const std::vector<std::shared_ptr<ASTNodeBase<> > >& getProgram() const
    {
      return program;
    }
  };

#endif // NODEPROGRAM_H
