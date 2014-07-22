/*
 * ExecutionVisitor.h
 *
 *  Created on: Jul 19, 2014
 *      Author: cmaier
 */

#ifndef EXECUTIONVISITOR_H_
#define EXECUTIONVISITOR_H_

#include <memory>
#include <iostream>

#include "../Database/DatabaseConnectorBase.h"
#include "../Formulas/IFormulaEvaluator.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionDecl.h"
#include "../../common/ASTNodeTypes/Statements/NodeProcExecution.h"
#include "../ExecutableElementsContainer.h"

#include "../../common/ASTNodeTypes/Statements/NodeAssignmentOperator.h"
#include "../SQLGenerator.h"
#include "../../common/ASTNodeTypes/Statements/NodeIDAssignment.h"

using namespace yagi::database;
using namespace yagi::container;
using namespace yagi::formula;

namespace yagi {
namespace execution {

class ExecutionVisitor: public ASTNodeVisitorBase,
    public Visitor<NodeActionDecl>,
    public Visitor<NodeConstant>,
    public Visitor<NodeProcExecution>,
    public Visitor<NodeActionPrecondition>,
    public Visitor<NodeIDAssignment>
{
  private:
    std::shared_ptr<IFormulaEvaluator> formulaEvaluator_;
    std::shared_ptr<DatabaseConnectorBase> db_;

  public:
    ExecutionVisitor();
    ExecutionVisitor(std::shared_ptr<IFormulaEvaluator> formulaEvaluator,
        std::shared_ptr<DatabaseConnectorBase> db);
    virtual ~ExecutionVisitor();

    Any visit(NodeActionDecl& actionDecl);
    Any visit(NodeConstant& formulaConstant);
    Any visit(NodeProcExecution& procExec);
    Any visit(NodeActionPrecondition& ap);
    Any visit(NodeIDAssignment& fluentAss);
};

}
/* namespace execution */
} /* namespace yagi */

#endif /* EXECUTIONVISITOR_H_ */
