/*
 * InterpretationVisitor.h
 *
 *  Created on: Jul 9, 2014
 *      Author: cmaier
 */

#ifndef INTERPRETATIONVISITOR_H_
#define INTERPRETATIONVISITOR_H_

#include <memory>

#include "../Database/DatabaseConnectorBase.h"
#include "../Database/DatabaseManager.h"
#include "../SQLGenerator.h"
#include "../../common/ASTNodeVisitorBase.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainStringElements.h"
#include "../../common/ASTNodeTypes/Statements/NodeVariableAssignment.h"
#include "../../common/ASTNodeTypes/Declarations/FluentDecl/NodeFluentDecl.h"
#include "../../common/ASTNodeTypes/Declarations/FactDecl/NodeFactDecl.h"
#include "../../common/ASTNodeTypes/Identifier/NodeID.h"
#include "../../common/ASTNodeTypes/ProgramStructure/NodeProgram.h"
#include "../../common/ASTNodeTypes/DataTypes/NodeString.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainString.h"
#include "../../common/ASTNodeTypes/Declarations/FactDecl/NodeFactDecl.h"
#include "../../common/ASTNodeTypes/Statements/NodeFluentQuery.h"
#include "../../common/ASTNodeTypes/Statements/NodeIDAssignment.h"
#include "../../common/ASTNodeTypes/Formula/NodeConstant.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionDecl.h"
#include "../../common/ASTNodeTypes/Statements/NodeProcExecution.h"
#include "../ExecutableElementsContainer.h"
#include "../FormulaEvaluator.h"
#include "ExecutionVisitor.h"
#include "../../front-end/astVisitors/ToStringVisitor.h"

using namespace yagi::database;
using namespace yagi::container;

namespace yagi {
namespace execution {

class InterpretationVisitor: public ASTNodeVisitorBase,
    public Visitor<NodeFluentDecl>,
    public Visitor<NodeFactDecl>,
    public Visitor<NodeActionDecl>,
    public Visitor<NodeProgram>,
    public Visitor<NodeFluentQuery>,
    public Visitor<NodeIDAssignment>,
    public Visitor<NodeProcExecution>
{
  private:
    std::string fluentDBDataToString(std::vector<std::vector<std::string>> data);

    static bool TypeOk(std::shared_ptr<ASTNodeBase<>> line)
    {
      bool ok = std::dynamic_pointer_cast<NodeFluentDecl>(line) != nullptr
          || std::dynamic_pointer_cast<NodeFactDecl>(line) != nullptr
          || std::dynamic_pointer_cast<NodeVariableAssignment>(line) != nullptr
          || std::dynamic_pointer_cast<NodeIDAssignment>(line) != nullptr
          || std::dynamic_pointer_cast<NodeActionDecl>(line) != nullptr
          || std::dynamic_pointer_cast<NodeExogenousEventDecl>(line) != nullptr
          || std::dynamic_pointer_cast<NodeProcDecl>(line) != nullptr
          || std::dynamic_pointer_cast<NodeFluentQuery>(line) != nullptr
          || std::dynamic_pointer_cast<NodeProcExecution>(line) != nullptr;

      if (!ok)
      {
        ToStringVisitor v;
        line->accept(v);
      }

      return ok;
    }

  public:
    InterpretationVisitor();
    virtual ~InterpretationVisitor();

    Any visit(NodeProgram& program);
    Any visit(NodeFluentDecl& fluentDecl);
    Any visit(NodeFactDecl& factDecl);
    Any visit(NodeActionDecl& actionDecl);
    Any visit(NodeFluentQuery& fluentQuery);
    Any visit(NodeIDAssignment& fluentAss);
    Any visit(NodeProcExecution& procExec);
};

} /* namespace execution */
} /* namespace yagi */

#endif /* INTERPRETATIONVISITOR_H_ */
