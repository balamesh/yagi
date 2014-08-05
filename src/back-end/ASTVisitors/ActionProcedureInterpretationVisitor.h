/*
 * ActionProcedureInterpretationVisitor.h
 *
 *  Created on: Jul 19, 2014
 *      Author: cmaier
 */

#ifndef ACTIONPROCEDUREINTERPRETATIONVISITOR_H_
#define ACTIONPROCEDUREINTERPRETATIONVISITOR_H_

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
#include "../../common/ASTNodeTypes/Identifier/NodeID.h"
#include "../Variables/VariableTableManager.h"
#include "../../common/ASTNodeTypes/Statements/NodeVariableAssignment.h"
#include "../../utils/SetOperations.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeSignal.h"
#include "../Signals/IYAGISignalHandler.h"
#include "../../common/ASTNodeTypes/Expressions/NodeValueExpression.h"
#include "../TreeHelper.h"
#include "../../common/ASTNodeTypes/Formula/NodeAtomConnective.h"
#include "../../common/ASTNodeTypes/Formula/NodeAtom.h"
#include "../../common/ASTNodeTypes/Formula/NodeNegation.h"
#include "../../common/ASTNodeTypes/Formula/NodeCompoundFormula.h"
#include "../../utils/DateTimeHelper.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainStringElements.h"
#include "../../common/ASTNodeTypes/Statements/NodeForLoop.h"
#include "../../common/ASTNodeTypes/Statements/NodeConditional.h"
#include "../../common/ASTNodeTypes/Declarations/ProcDecl/NodeProcDecl.h"
#include "../../common/ASTNodeTypes/Statements/NodePick.h"
#include "../../utils/RandomNumberGenerator.h"
#include "../../common/ASTNodeTypes/Statements/NodeChoose.h"
#include "../../common/ASTNodeTypes/Statements/NodeWhileLoop.h"
#include "../Database/DBHelper.h"

using namespace yagi::database;
using namespace yagi::container;
using namespace yagi::formula;

namespace yagi {
namespace execution {

class ActionProcedureInterpretationVisitor: public ASTNodeVisitorBase,
    public Visitor<NodeActionDecl>,
    public Visitor<NodeConstant>,
    public Visitor<NodeProcExecution>,
    public Visitor<NodeActionPrecondition>,
    public Visitor<NodeIDAssignment>,
    public Visitor<NodeID>,
    public Visitor<NodeSet>,
    public Visitor<NodeSetExpression>,
    public Visitor<NodeTuple>,
    public Visitor<NodeVariable>,
    public Visitor<NodeString>,
    public Visitor<NodeVariableAssignment>,
    public Visitor<NodeAssignmentOperator>,
    public Visitor<NodeSignal>,
    public Visitor<NodeValueExpression>,
    public Visitor<NodeAtomConnective>,
    public Visitor<NodeAtom>,
    public Visitor<NodeNegation>,
    public Visitor<NodeCompoundFormula>,
    public Visitor<NodeFormulaConnective>,
    public Visitor<NodeQuantifiedFormula>,
    public Visitor<NodeOperatorIn>,
    public Visitor<NodeFluentDecl>,
    public Visitor<NodeForLoop>,
    public Visitor<NodeConditional>,
    public Visitor<NodeVarList>,
    public Visitor<NodeProcDecl>,
    public Visitor<NodeValueList>,
    public Visitor<NodePick>,
    public Visitor<NodeChoose>,
    public Visitor<NodeWhileLoop>

{
  private:
    std::shared_ptr<IFormulaEvaluator> formulaEvaluator_;
    std::shared_ptr<DatabaseConnectorBase> db_;
    std::shared_ptr<IYAGISignalHandler> signalReceiver_;
    Any triggerYagiSignal(NodeSignal& signal, std::vector<std::string> settingVariables);

  public:
    ActionProcedureInterpretationVisitor();
    ActionProcedureInterpretationVisitor(std::shared_ptr<IFormulaEvaluator> formulaEvaluator,
        std::shared_ptr<DatabaseConnectorBase> db, std::shared_ptr<IYAGISignalHandler> signalReceiver);
    ActionProcedureInterpretationVisitor(std::shared_ptr<DatabaseConnectorBase> db);
    virtual ~ActionProcedureInterpretationVisitor();

    Any visit(NodeActionDecl& actionDecl);
    Any visit(NodeConstant& formulaConstant);
    Any visit(NodeProcExecution& procExec);
    Any visit(NodeActionPrecondition& ap);
    Any visit(NodeIDAssignment& idAssign);
    Any visit(NodeID& id);
    Any visit(NodeSet& set);
    Any visit(NodeSetExpression& setExpr);
    Any visit(NodeTuple& tuple);
    Any visit(NodeVariable& variable);
    Any visit(NodeString& str);
    Any visit(NodeVariableAssignment& varAss);
    Any visit(NodeAssignmentOperator& assOp);
    Any visit(NodeSignal& signal);
    Any visit(NodeValueExpression& valExpr);
    Any visit(NodeAtomConnective& atomConnective);
    Any visit(NodeAtom& atom);
    Any visit(NodeNegation& negation);
    Any visit(NodeCompoundFormula& compoundFormula);
    Any visit(NodeFormulaConnective& formulaConnective);
    Any visit(NodeQuantifiedFormula& quantifiedFormula);
    Any visit(NodeOperatorIn& inFormula);
    Any visit(NodeFluentDecl& fluentDecl);
    Any visit(NodeForLoop& forLoop);
    Any visit(NodeConditional& conditional);
    Any visit(NodeVarList& varList);
    Any visit(NodeProcDecl& procDecl);
    Any visit(NodeValueList& valueList);
    Any visit(NodePick& pick);
    Any visit(NodeChoose& choose);
    Any visit(NodeWhileLoop& whileLoop);
};

}
/* namespace execution */
} /* namespace yagi */

#endif /* ACTIONPROCEDUREINTERPRETATIONVISITOR_H_ */
