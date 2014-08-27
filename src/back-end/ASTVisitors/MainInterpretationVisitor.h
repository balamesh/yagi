/*
 * MainInterpretationVisitor.h
 *
 *  Created on: Jul 9, 2014
 *      Author: cmaier
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
    void initDB();

  public:
    MainInterpretationVisitor();
    virtual ~MainInterpretationVisitor();

    Any visit(NodeProgram& program);
    Any visit(NodeFluentDecl& fluentDecl);
    Any visit(NodeFactDecl& factDecl);
    Any visit(NodeActionDecl& actionDecl);
    Any visit(NodeFluentQuery& fluentQuery);
    Any visit(NodeIDAssignment& fluentAss);
    Any visit(NodeProcExecution& procExec);
    Any visit(NodeSet& set);
    Any visit(NodeSetExpression& setExpr);
    Any visit(NodeTuple& tuple);
    Any visit(NodeVariable& variable);
    Any visit(NodeString& str);
    Any visit(NodeID& id);
    Any visit(NodeVariableAssignment& varAss);
    Any visit(NodeForLoop& forLoop);
    Any visit(NodeConditional& conditional);
    Any visit(NodeProcDecl& procDecl);
    Any visit(NodeExogenousEventDecl& nodeExoEventDecl);
    Any visit(NodeSearch& nodeSearch);
    Any visit(NodeTest& nodeTest);
    Any visit(NodeChoose& nodeChoose);
    Any visit(NodePick& nodePick);
    Any visit(NodeWhileLoop& nodeWhileLoop);
};

} /* namespace execution */
} /* namespace yagi */

#endif /* MAININTERPRETATIONVISITOR_H_ */
