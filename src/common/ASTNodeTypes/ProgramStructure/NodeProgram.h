#ifndef NODEPROGRAM_H
#define NODEPROGRAM_H

#include<vector>
#include<memory>
#include <algorithm>
#include <iostream>

#include "../ASTNodeBase.h"
#include "../Declarations/FluentDecl/NodeFluentDecl.h"
#include "../Declarations/FactDecl/NodeFactDecl.h"
#include "../Declarations/ProcDecl/NodeProcDecl.h"
#include "../Statements/NodeVariableAssignment.h"
#include "../Statements/NodeIDAssignment.h"
#include "../Declarations/ActionDecl/NodeActionDecl.h"
#include "../Declarations/ExogenousEventDecl/NodeExogenousEventDecl.h"
#include "../Statements/NodeStatementBase.h"

class NodeProgram: public ASTNodeBase<>
{
  private:
    std::vector<std::shared_ptr<ASTNodeBase<>>> program;

    static bool TypeOk(std::shared_ptr<ASTNodeBase<>> line)
    {
      return (std::dynamic_pointer_cast<NodeFluentDecl>(line) != nullptr
          || std::dynamic_pointer_cast<NodeFactDecl>(line) != nullptr
          || std::dynamic_pointer_cast<NodeVariableAssignment>(line) != nullptr
          || std::dynamic_pointer_cast<NodeIDAssignment>(line) != nullptr
          || std::dynamic_pointer_cast<NodeActionDecl>(line) != nullptr
          || std::dynamic_pointer_cast<NodeExogenousEventDecl>(line) != nullptr
          || std::dynamic_pointer_cast<NodeStatementBase>(line) != nullptr
          || std::dynamic_pointer_cast<NodeProcDecl>(line) != nullptr
      );
    }

  public:
    DEFINE_VISITABLE()
    void addStatementToProgram(std::shared_ptr<ASTNodeBase<>> statement)
    {
      program.insert(std::begin(program), statement);
    }

    NodeProgram();
    virtual ~NodeProgram();

//    virtual void accept(ASTNodeVisitorBase* visitor) override
//    {
//      std::for_each(program.begin(), program.end(), [&visitor](std::shared_ptr<ASTNodeBase> stmt)
//      {
//        //safety net to check if only valid YAGI lines and not any
//        //garbage resulting from a bug is considered a line...
//          if (!TypeOk(stmt))
//          {
//            throw std::runtime_error("Invalid node type left on program-level of AST!");
//          }
//
//          stmt->accept(visitor);
//        });
//
//      visitor->visit(this);
//    }

    const std::vector<std::shared_ptr<ASTNodeBase<> > >& getProgram() const
    {
      return program;
    }
};

#endif // NODEPROGRAM_H
