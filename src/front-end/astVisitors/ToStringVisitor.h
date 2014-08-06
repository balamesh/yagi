/*
 * ToStringVisitor.h
 *
 *  Created on: May 22, 2014
 *      Author: cmaier
 */

#ifndef TOSTRINGVISITOR_H_
#define TOSTRINGVISITOR_H_

#include <iostream>
#include <memory>
#include <vector>

#include "../../common/ASTNodeVisitorBase.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainStringElements.h"
#include "../../common/ASTNodeTypes/Declarations/FluentDecl/NodeFluentDecl.h"
#include "../../common/ASTNodeTypes/Identifier/NodeID.h"
#include "../../common/ASTNodeTypes/ProgramStructure/NodeProgram.h"
#include "../../common/ASTNodeTypes/DataTypes/NodeString.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainString.h"
#include "../../common/ASTNodeTypes/Declarations/FactDecl/NodeFactDecl.h"
#include "../../common/ASTNodeTypes/Statements/NodeFluentQuery.h"
#include "../../common/ASTNodeTypes/Statements/NodeIDAssignment.h"
#include "../../common/ASTNodeTypes/Expressions/NodeExpressionOperator.h"
#include "../../common/ASTNodeTypes/Expressions/NodeSetExpression.h"
#include "../../common/ASTNodeTypes/Expressions/NodeValueExpression.h"
#include "../../common/ASTNodeTypes/Set/NodeSet.h"
#include "../../common/ASTNodeTypes/Tuple/NodeTuple.h"
#include "../../common/ASTNodeTypes/Formula/NodeAtom.h"
#include "../../common/ASTNodeTypes/Formula/NodeAtomConnective.h"
#include "../../common/ASTNodeTypes/Formula/NodeCompoundFormula.h"
#include "../../common/ASTNodeTypes/Formula/NodeFormulaConnective.h"
#include "../../common/ASTNodeTypes/Formula/NodeNegation.h"
#include "../../common/ASTNodeTypes/Formula/NodeOperatorIn.h"
#include "../../common/ASTNodeTypes/Formula/NodeQuantifiedFormula.h"
#include "../../common/ASTNodeTypes/Formula/NodeConstant.h"
#include "../../common/ASTNodeTypes/Variables/NodeVariable.h"
#include "../../common/ASTNodeTypes/Variables/NodeVarList.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeSignal.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionEffect.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionPrecondition.h"
#include "../../common/ASTNodeTypes/Declarations/SensingDecl/NodeSensingDecl.h"
#include "../../common/ASTNodeTypes/Declarations/ProcDecl/NodeProcDecl.h"
#include "../../common/ASTNodeTypes/Statements/NodeBlock.h"
#include "../../common/ASTNodeTypes/Statements/NodeChoose.h"
#include "../../common/ASTNodeTypes/Statements/NodeConditional.h"
#include "../../common/ASTNodeTypes/Statements/NodeForLoop.h"
#include "../../common/ASTNodeTypes/Statements/NodePick.h"
#include "../../common/ASTNodeTypes/Statements/NodeProcExecution.h"
#include "../../common/ASTNodeTypes/Statements/NodeSearch.h"
#include "../../common/ASTNodeTypes/Statements/NodeTest.h"
#include "../../common/ASTNodeTypes/Statements/NodeVariableAssignment.h"
#include "../../common/ASTNodeTypes/Statements/NodeWhileLoop.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionDecl.h"
#include "../../common/ASTNodeTypes/DataTypes/NodeIncompleteKnowledge.h"
#include "../../common/ASTNodeTypes/DataTypes/NodePatternMatching.h"
#include "../../common/ASTNodeTypes/DataTypes/NodeValueList.h"
#include "../../common/ASTNodeTypes/Declarations/ExogenousEventDecl/NodeExogenousEventDecl.h"
#include "../../common/ASTNodeTypes/Statements/NodeAssignmentOperator.h"
#include "../../common/ASTNodeTypes/Statements/NodeSitCalcActionExecution.h"

using namespace yagi::container;

class ToStringVisitor: public ASTNodeVisitorBase,
    public Visitor<NodeFluentDecl>,
    public Visitor<NodeDomainString>,
    public Visitor<NodeDomainStringElements>,
    public Visitor<NodeID>,
    public Visitor<NodeProgram>,
    public Visitor<NodeString>,
    public Visitor<NodeFactDecl>,
    public Visitor<NodeFluentQuery>,
    public Visitor<NodeIDAssignment>,
    public Visitor<NodeAssignmentOperator>,
    public Visitor<NodeSetExpression>,
    public Visitor<NodeSet>,
    public Visitor<NodeTuple>,
    public Visitor<NodeConstant>,
    public Visitor<NodeActionDecl>,
    public Visitor<NodeActionPrecondition>,
    public Visitor<NodeActionEffect>,
    public Visitor<NodeIncompleteKnowledge>,
    public Visitor<NodePatternMatching>,
    public Visitor<NodeSignal>,
    public Visitor<NodeExogenousEventDecl>,
    public Visitor<NodeProcDecl>,
    public Visitor<NodeSensingDecl>,
    public Visitor<NodeCompoundFormula>,
    public Visitor<NodeFormulaConnective>,
    public Visitor<NodeValueList>,
    public Visitor<NodeValueExpression>,
    public Visitor<NodeExpressionOperator>,
    public Visitor<NodeAtom>,
    public Visitor<NodeAtomConnective>,
    public Visitor<NodeNegation>,
    public Visitor<NodeOperatorIn>,
    public Visitor<NodeQuantifiedFormula>,
    public Visitor<NodeVariable>,
    public Visitor<NodeVarList>,
    public Visitor<NodeBlock>,
    public Visitor<NodeChoose>,
    public Visitor<NodeConditional>,
    public Visitor<NodeForLoop>,
    public Visitor<NodePick>,
    public Visitor<NodeProcExecution>,
    public Visitor<NodeSearch>,
    public Visitor<NodeTest>,
    public Visitor<NodeVariableAssignment>,
    public Visitor<NodeWhileLoop>,
    public Visitor<NodeSitCalcActionExecution>
{
  public:
    Any visit(NodeProgram& program);
    Any visit(NodeFluentDecl& fluentDecl);
    Any visit(NodeFactDecl& factDecl);
    Any visit(NodeDomainString& domainString);
    Any visit(NodeID& id);
    Any visit(NodeString& str);
    Any visit(NodeDomainStringElements& domainStringElems);
    Any visit(NodeFluentQuery& fluentQuery);
    Any visit(NodeIDAssignment& fluentAss);
    Any visit(NodeAssignmentOperator& setExprOp);
    Any visit(NodeSetExpression& setExpr);
    Any visit(NodeSet& set);
    Any visit(NodeTuple& tuple);
    Any visit(NodeConstant& constant);
    Any visit(NodeActionDecl& actionDecl);
    Any visit(NodeActionPrecondition& precondition);
    Any visit(NodeActionEffect& effect);
    Any visit(NodeIncompleteKnowledge& incompleteKnowledge);
    Any visit(NodePatternMatching& patternMatching);
    Any visit(NodeValueList& valueList);
    Any visit(NodeSignal& signal);
    Any visit(NodeExogenousEventDecl& exoEvent);
    Any visit(NodeProcDecl& procDecl);
    Any visit(NodeSensingDecl& sensingDecl);
    Any visit(NodeExpressionOperator& valExprOp);
    Any visit(NodeValueExpression& valExpr);
    Any visit(NodeAtom& atom);
    Any visit(NodeAtomConnective& connective);
    Any visit(NodeCompoundFormula& compoundFormula);
    Any visit(NodeFormulaConnective& connective);
    Any visit(NodeNegation& negation);
    Any visit(NodeOperatorIn& inFormula);
    Any visit(NodeQuantifiedFormula& quantifiedFormula);
    Any visit(NodeVariable& variable);
    Any visit(NodeVarList& varList);
    Any visit(NodeBlock& block);
    Any visit(NodeChoose& choose);
    Any visit(NodeConditional& conditional);
    Any visit(NodeForLoop& forLoop);
    Any visit(NodePick& pick);
    Any visit(NodeProcExecution& procExec);
    Any visit(NodeSearch& search);
    Any visit(NodeTest& test);
    Any visit(NodeVariableAssignment& varAssignment);
    Any visit(NodeWhileLoop& whileLoop);
    Any visit(NodeSitCalcActionExecution& sitCalcActionExec);
};

#endif /* TOSTRINGVISITOR_H_ */
