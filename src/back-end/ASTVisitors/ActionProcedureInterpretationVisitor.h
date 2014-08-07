/*
 * ActionProcedureInterpretationVisitor.h
 *
 *  Created on: Jul 19, 2014
 *      Author: cmaier
 */

#ifndef ACTIONPROCEDUREINTERPRETATIONVISITOR_H_
#define ACTIONPROCEDUREINTERPRETATIONVISITOR_H_

#include <memory>
#include <string>
#include <vector>

#include "../../common/ASTNodeTypes/DataTypes/NodeString.h"
#include "../../common/ASTNodeTypes/DataTypes/NodeValueList.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionDecl.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionPrecondition.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeSignal.h"
#include "../../common/ASTNodeTypes/Declarations/FluentDecl/NodeFluentDecl.h"
#include "../../common/ASTNodeTypes/Declarations/ProcDecl/NodeProcDecl.h"
#include "../../common/ASTNodeTypes/Expressions/NodeSetExpression.h"
#include "../../common/ASTNodeTypes/Expressions/NodeValueExpression.h"
#include "../../common/ASTNodeTypes/Formula/NodeAtom.h"
#include "../../common/ASTNodeTypes/Formula/NodeAtomConnective.h"
#include "../../common/ASTNodeTypes/Formula/NodeCompoundFormula.h"
#include "../../common/ASTNodeTypes/Formula/NodeConstant.h"
#include "../../common/ASTNodeTypes/Formula/NodeFormulaConnective.h"
#include "../../common/ASTNodeTypes/Formula/NodeNegation.h"
#include "../../common/ASTNodeTypes/Formula/NodeOperatorIn.h"
#include "../../common/ASTNodeTypes/Formula/NodeQuantifiedFormula.h"
#include "../../common/ASTNodeTypes/Identifier/NodeID.h"
#include "../../common/ASTNodeTypes/Set/NodeSet.h"
#include "../../common/ASTNodeTypes/Statements/NodeAssignmentOperator.h"
#include "../../common/ASTNodeTypes/Statements/NodeChoose.h"
#include "../../common/ASTNodeTypes/Statements/NodeConditional.h"
#include "../../common/ASTNodeTypes/Statements/NodeForLoop.h"
#include "../../common/ASTNodeTypes/Statements/NodeIDAssignment.h"
#include "../../common/ASTNodeTypes/Statements/NodePick.h"
#include "../../common/ASTNodeTypes/Statements/NodeProcExecution.h"
#include "../../common/ASTNodeTypes/Statements/NodeSitCalcActionExecution.h"
#include "../../common/ASTNodeTypes/Statements/NodeTest.h"
#include "../../common/ASTNodeTypes/Statements/NodeVariableAssignment.h"
#include "../../common/ASTNodeTypes/Statements/NodeWhileLoop.h"
#include "../../common/ASTNodeTypes/Tuple/NodeTuple.h"
#include "../../common/ASTNodeTypes/Variables/NodeVariable.h"
#include "../../common/ASTNodeTypes/Variables/NodeVarList.h"
#include "../../common/ASTNodeVisitorBase.h"
#include "../../common/ASTNodeTypes/Statements/NodeSearch.h"
#include "../../common/ASTNodeTypes/Statements/NodeBlock.h"

namespace yagi {
namespace execution {
class VariableTable;
} /* namespace execution */
} /* namespace yagi */

namespace yagi {
namespace database {
class DatabaseConnectorBase;
} /* namespace database */
namespace execution {
class IYAGISignalHandler;
} /* namespace execution */
namespace formula {
class IFormulaEvaluator;
} /* namespace formula */
} /* namespace yagi */

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
    public Visitor<NodeWhileLoop>,
    public Visitor<NodeTest>,
    public Visitor<NodeSitCalcActionExecution>,
    public Visitor<NodeSearch>,
    public Visitor<NodeBlock>

{
  private:
    std::shared_ptr<yagi::formula::IFormulaEvaluator> formulaEvaluator_;
    std::shared_ptr<yagi::database::DatabaseConnectorBase> db_;
    std::shared_ptr<IYAGISignalHandler> signalReceiver_;
    yagi::execution::VariableTable* varTable_;
    Any triggerYagiSignal(NodeSignal& signal, std::vector<std::string> settingVariables);

  public:
    ActionProcedureInterpretationVisitor();
    ActionProcedureInterpretationVisitor(
        std::shared_ptr<yagi::formula::IFormulaEvaluator> formulaEvaluator,
        std::shared_ptr<yagi::database::DatabaseConnectorBase> db,
        std::shared_ptr<IYAGISignalHandler> signalReceiver, VariableTable& varTable);
    ActionProcedureInterpretationVisitor(std::shared_ptr<yagi::database::DatabaseConnectorBase> db);
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
    Any visit(NodeTest& test);
    Any visit(NodeSitCalcActionExecution& sitCalcAction);
    Any visit(NodeSearch& search);
    Any visit(NodeBlock& block);
};

}
/* namespace execution */
} /* namespace yagi */

#endif /* ACTIONPROCEDUREINTERPRETATIONVISITOR_H_ */
