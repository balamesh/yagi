/**
 * @file   MainInterpretationVisitor.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Responsible for executing a YAGI program, i.e. the main interpretation visitor is
 * directly invoked from the GUI, i.e. it is the main entry point of the execution of a YAGI program.
 * It either redirects execution to a ActionProcedureInterpretation visitor instance or executes
 * directly if the execution semantics differ from the semantics of the ActionProcedureInterpretation
 * implementation
 */

#ifndef MAININTERPRETATIONVISITOR_H_
#define MAININTERPRETATIONVISITOR_H_

#include <memory>

#include "../../common/ASTNodeTypes/ASTNodeBase.h"
#include "../../common/ASTNodeTypes/DataTypes/NodeString.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionDecl.h"
#include "../../common/ASTNodeTypes/Declarations/ExogenousEventDecl/NodeExogenousEventDecl.h"
#include "../../common/ASTNodeTypes/Declarations/FactDecl/NodeFactDecl.h"
#include "../../common/ASTNodeTypes/Declarations/FluentDecl/NodeFluentDecl.h"
#include "../../common/ASTNodeTypes/Declarations/ProcDecl/NodeProcDecl.h"
#include "../../common/ASTNodeTypes/Expressions/NodeSetExpression.h"
#include "../../common/ASTNodeTypes/Identifier/NodeID.h"
#include "../../common/ASTNodeTypes/ProgramStructure/NodeProgram.h"
#include "../../common/ASTNodeTypes/Set/NodeSet.h"
#include "../../common/ASTNodeTypes/Statements/NodeConditional.h"
#include "../../common/ASTNodeTypes/Statements/NodeFluentQuery.h"
#include "../../common/ASTNodeTypes/Statements/NodeForLoop.h"
#include "../../common/ASTNodeTypes/Statements/NodeIDAssignment.h"
#include "../../common/ASTNodeTypes/Statements/NodeProcExecution.h"
#include "../../common/ASTNodeTypes/Statements/NodeSearch.h"
#include "../../common/ASTNodeTypes/Statements/NodeVariableAssignment.h"
#include "../../common/ASTNodeTypes/Tuple/NodeTuple.h"
#include "../../common/ASTNodeTypes/Variables/NodeVariable.h"
#include "../../common/ASTNodeVisitorBase.h"
#include "../../front-end/astVisitors/ToStringVisitor.h"
#include "../../utils/Any.h"
#include "../../common/ASTNodeTypes/Statements/NodeTest.h"
#include "../../common/ASTNodeTypes/Statements/NodeChoose.h"
#include "../../common/ASTNodeTypes/Statements/NodePick.h"
#include "../../common/ASTNodeTypes/Statements/NodeWhileLoop.h"

using namespace yagi::container;

namespace yagi {
namespace execution {

/**
 * Responsible for executing a YAGI program, i.e. the main interpretation visitor is
 * directly invoked from the GUI, i.e. it is the main entry point of the execution of a YAGI program.
 */
class MainInterpretationVisitor: public ASTNodeVisitorBase,
    public Visitor<NodeFluentDecl>,
    public Visitor<NodeFactDecl>,
    public Visitor<NodeActionDecl>,
    public Visitor<NodeFluentQuery>,
    public Visitor<NodeIDAssignment>,
    public Visitor<NodeProcExecution>,
    public Visitor<NodeSet>,
    public Visitor<NodeSetExpression>,
    public Visitor<NodeTuple>,
    public Visitor<NodeVariable>,
    public Visitor<NodeString>,
    public Visitor<NodeID>,
    public Visitor<NodeVariableAssignment>,
    public Visitor<NodeForLoop>,
    public Visitor<NodeConditional>,
    public Visitor<NodeProcDecl>,
    public Visitor<NodeExogenousEventDecl>,
    public Visitor<NodeSearch>,
    public Visitor<NodeTest>,
    public Visitor<NodeChoose>,
    public Visitor<NodePick>,
    public Visitor<NodeWhileLoop>
{
  private:
    /**
     * Initializes the main database instance
     */
    void initDB();

  public:
    /**
     * Default ctor
     */
    MainInterpretationVisitor();

    /**
     * Default dtor
     */
    virtual ~MainInterpretationVisitor();

    /**
     * Visit method for the root node of a YAGI program
     * XXX Currently unused, remove!
     * @param program The YAGI program node
     * @return Nothing
     */
    Any visit(NodeProgram& program);

    /**
     * Visit method for fluent declaration
     * @param fluentDecl The fluent declaration node
     * @return Whatever the ActionProcedureInterpreationVisitor returns
     */
    Any visit(NodeFluentDecl& fluentDecl);

    /**
     * Visit method for fact declaration
     * @param factDecl The fact decl. node
     * @return Nothing
     */
    Any visit(NodeFactDecl& factDecl);

    /**
     * Visit method for action declaration
     * @param actionDecl The action declaration node
     * @return Nothing
     */
    Any visit(NodeActionDecl& actionDecl);

    /**
     * Visit method for fluent query
     * @param fluentQuery The fluent query node
     * @return Nothing
     */
    Any visit(NodeFluentQuery& fluentQuery);

    /**
     * Visit method for fluent assignment
     * @param fluentAss The fluent assignment node
     * @return Whatever the ActionProcedureInterpreationVisitor returns
     */
    Any visit(NodeIDAssignment& fluentAss);

    /**
     * Visit method for YAGI procedure execution
     * @param procExec The procedure execution node
     * @return Whatever the ActionProcedureInterpreationVisitor returns
     */
    Any visit(NodeProcExecution& procExec);

    /**
     * Visit method for a YAGI set
     * @param set The set node
     * @return Whatever the ActionProcedureInterpreationVisitor returns
     */
    Any visit(NodeSet& set);

    /**
     * Visit method for a set expression
     * @param setExpr The set expression node
     * @return Whatever the ActionProcedureInterpreationVisitor returns
     */
    Any visit(NodeSetExpression& setExpr);

    /**
     * Visit method for a YAGI tuple
     * @param tuple The tuple node
     * @return Whatever the ActionProcedureInterpreationVisitor returns
     */
    Any visit(NodeTuple& tuple);

    /**
     * Visit method for a YAGI variable
     * @param variable The variable node
     * @return Whatever the ActionProcedureInterpreationVisitor returns
     */
    Any visit(NodeVariable& variable);

    /**
     * Visit method for a YAGI string
     * @param str The string node
     * @return Whatever the ActionProcedureInterpreationVisitor returns
     */
    Any visit(NodeString& str);

    /**
     * Visit method for a YAGI identifier
     * @param id The identifier node
     * @return Whatever the ActionProcedureInterpreationVisitor returns
     */
    Any visit(NodeID& id);

    /**
     * Visit method for a variable assignment
     * @param varAss The assignment node
     * @return Whatever the ActionProcedureInterpreationVisitor returns
     */
    Any visit(NodeVariableAssignment& varAss);

    /**
     * Visit method for a YAGI for-loop
     * @param forLoop The for-loop node
     * @return Whatever the ActionProcedureInterpreationVisitor returns
     */
    Any visit(NodeForLoop& forLoop);

    /**
     * Visit method for YAGI conditionals
     * @param conditional The conditional node
     * @return Whatever the ActionProcedureInterpreationVisitor returns
     */
    Any visit(NodeConditional& conditional);

    /**
     * Visit method for a procedure declaration
     * @param procDecl The proc. decl node
     * @return Nothing
     */
    Any visit(NodeProcDecl& procDecl);

    /**
     * Visit method for exogenous event declarations
     * @param nodeExoEventDecl The exo event decl node
     * @return Nothing
     */
    Any visit(NodeExogenousEventDecl& nodeExoEventDecl);

    /**
     * Visit method for search statement
     * @param nodeSearch The search node
     * @return Whatever the ActionProcedureInterpreationVisitor returns
     */
    Any visit(NodeSearch& nodeSearch);

    /**
     * Visit method for test statement
     * @param nodeTest The test node
     * @return Whatever the ActionProcedureInterpreationVisitor returns
     */
    Any visit(NodeTest& nodeTest);

    /**
     * Visit method for a choose statement
     * @param nodeChoose The choose node
     * @return Whatever the ActionProcedureInterpreationVisitor returns
     */
    Any visit(NodeChoose& nodeChoose);

    /**
     * Visit method for a pick statement
     * @param nodePick The pick node
     * @return Whatever the ActionProcedureInterpreationVisitor returns
     */
    Any visit(NodePick& nodePick);

    /**
     * Visit method for a YAGI while-loop
     * @param nodeWhileLoop The while-loop node
     * @return Whatever the ActionProcedureInterpreationVisitor returns
     */
    Any visit(NodeWhileLoop& nodeWhileLoop);
};

} /* namespace execution */
} /* namespace yagi */

#endif /* MAININTERPRETATIONVISITOR_H_ */
