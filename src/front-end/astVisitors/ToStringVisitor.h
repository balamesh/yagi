/**
 * @file   ToStringVisitor.h
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * Prints a string representation of the C++ AST structure. Primarily used for debugging.
 *
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

/**
 * Pretty printer class for the C++ AST.
 */
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
    /**
     * Visitor method for program node
     * @param program AST Node
     * @return String version of the AST
     */
    Any visit(NodeProgram& program);

    /**
     * Visitor method for fluent decl node
     * @param fluentDecl AST Node
     * @return String version of the AST
     */
    Any visit(NodeFluentDecl& fluentDecl);

    /**
     * Visitor method for fact decl node
     * @param factDecl AST Node
     * @return String version of the AST
     */
    Any visit(NodeFactDecl& factDecl);

    /**
     * Visitor method for string domain node
     * @param domainString AST Node
     * @return String version of the AST
     */
    Any visit(NodeDomainString& domainString);

    /**
     * Visitor method for ID node
     * @param id AST Node
     * @return String version of the AST
     */
    Any visit(NodeID& id);

    /**
     * Visitor method for String node
     * @param str AST Node
     * @return String version of the AST
     */
    Any visit(NodeString& str);

    /**
     * Visitor method for string domain
     * @param domainStringElems AST Node
     * @return String version of the AST
     */
    Any visit(NodeDomainStringElements& domainStringElems);

    /**
     * Visitor method for fluent query
     * @param fluentQuery AST Node
     * @return String version of the AST
     */
    Any visit(NodeFluentQuery& fluentQuery);

    /**
     * Visitor method for fluent assignment
     * @param fluentAss AST Node
     * @return String version of the AST
     */
    Any visit(NodeIDAssignment& fluentAss);

    /**
     * Visitor method for set expression operator
     * @param setExprOp AST Node
     * @return String version of the AST
     */
    Any visit(NodeAssignmentOperator& setExprOp);

    /**
     * Visitor method for set expression
     * @param setExpr AST Node
     * @return String version of the AST
     */
    Any visit(NodeSetExpression& setExpr);

    /**
     * Visitor method for Set
     * @param set AST Node
     * @return String version of the AST
     */
    Any visit(NodeSet& set);

    /**
     * Visitor method for tuple
     * @param tuple AST Node
     * @return String version of the AST
     */
    Any visit(NodeTuple& tuple);

    /**
     * Visitor method for constant
     * @param constant AST Node
     * @return String version of the AST
     */
    Any visit(NodeConstant& constant);

    /**
     * Visitor method for action declaration
     * @param actionDecl AST Node
     * @return String version of the AST
     */
    Any visit(NodeActionDecl& actionDecl);

    /**
     * Visitor method for action precondition
     * @param precondition AST Node
     * @return String version of the AST
     */
    Any visit(NodeActionPrecondition& precondition);

    /**
     * Visitor method for action effect
     * @param effect AST Node
     * @return String version of the AST
     */
    Any visit(NodeActionEffect& effect);

    /**
     * Visitor method for incomplete knowledge
     * @param incompleteKnowledge AST Node
     * @return String version of the AST
     */
    Any visit(NodeIncompleteKnowledge& incompleteKnowledge);

    /**
     * Visitor method for pattern matching
     * @param patternMatching AST Node
     * @return String version of the AST
     */
    Any visit(NodePatternMatching& patternMatching);

    /**
     * Visitor method for value list
     * @param valueList AST Node
     * @return String version of the AST
     */
    Any visit(NodeValueList& valueList);

    /**
     * Visitor method for signal
     * @param signal AST Node
     * @return String version of the AST
     */
    Any visit(NodeSignal& signal);

    /**
     * Visitor method for exogenous event
     * @param exoEvent AST Node
     * @return String version of the AST
     */
    Any visit(NodeExogenousEventDecl& exoEvent);

    /**
     * Visitor method for procedure declaration
     * @param procDecl AST Node
     * @return String version of the AST
     */
    Any visit(NodeProcDecl& procDecl);

    /**
     * Visitor method for sensing declaration
     * @param sensingDecl AST Node
     * @return String version of the AST
     */
    Any visit(NodeSensingDecl& sensingDecl);

    /**
     * Visitor method for value expression operator
     * @param valExprOp AST Node
     * @return String version of the AST
     */
    Any visit(NodeExpressionOperator& valExprOp);

    /**
     * Visitor method for value expression
     * @param valExpr AST Node
     * @return String version of the AST
     */
    Any visit(NodeValueExpression& valExpr);

    /**
     * Visitor method for atom
     * @param atom AST Node
     * @return String version of the AST
     */
    Any visit(NodeAtom& atom);

    /**
     * Visitor method for atom connective
     * @param connective AST Node
     * @return String version of the AST
     */
    Any visit(NodeAtomConnective& connective);

    /**
     * Visitor method for compound formula
     * @param compoundFormula AST Node
     * @return String version of the AST
     */
    Any visit(NodeCompoundFormula& compoundFormula);

    /**
     * Visitor method of formula connective
     * @param connective AST Node
     * @return String version of the AST
     */
    Any visit(NodeFormulaConnective& connective);

    /**
     * Visitor method of negation
     * @param negation AST Node
     * @return String version of the AST
     */
    Any visit(NodeNegation& negation);

    /**
     * Visitor method of operator 'in' formula
     * @param inFormula AST Node
     * @return String version of the AST
     */
    Any visit(NodeOperatorIn& inFormula);

    /**
     * Visitor method for quantified formula
     * @param quantifiedFormula AST Node
     * @return String version of the AST
     */
    Any visit(NodeQuantifiedFormula& quantifiedFormula);

    /**
     * Visitor method for variable
     * @param variable AST Node
     * @return String version of the AST
     */
    Any visit(NodeVariable& variable);

    /**
     * Visitor method for variable list
     * @param varList AST Node
     * @return String version of the AST
     */
    Any visit(NodeVarList& varList);

    /**
     * Visitor method for block
     * @param block AST Node
     * @return String version of the AST
     */
    Any visit(NodeBlock& block);

    /**
     * Visitor method for choose
     * @param choose AST Node
     * @return String version of the AST
     */
    Any visit(NodeChoose& choose);

    /**
     * Visitor method for conditional
     * @param conditional AST Node
     * @return String version of the AST
     */
    Any visit(NodeConditional& conditional);

    /**
     * Visitor method for for-loop
     * @param forLoop AST Node
     * @return String version of the AST
     */
    Any visit(NodeForLoop& forLoop);

    /**
     * Visitor method for pick statement
     * @param pick AST Node
     * @return String version of the AST
     */
    Any visit(NodePick& pick);

    /**
     * Visitor method for procedure execution
     * @param procExec AST Node
     * @return String version of the AST
     */
    Any visit(NodeProcExecution& procExec);

    /**
     * Visitor method for search
     * @param search AST Node
     * @return String version of the AST
     */
    Any visit(NodeSearch& search);

    /**
     * Visitor method for test statement
     * @param test AST Node
     * @return String version of the AST
     */
    Any visit(NodeTest& test);

    /**
     * Visitor method for a variable assignment
     * @param varAssignment AST Node
     * @return String version of the AST
     */
    Any visit(NodeVariableAssignment& varAssignment);

    /**
     * Visitor method for a while loop
     * @param whileLoop AST Node
     * @return String version of the AST
     */
    Any visit(NodeWhileLoop& whileLoop);

    /**
     * Visitor method for a sit calc action (add/remove)
     * @param sitCalcActionExec AST Node
     * @return String version of the AST
     */
    Any visit(NodeSitCalcActionExecution& sitCalcActionExec);
};

#endif /* TOSTRINGVISITOR_H_ */
