/**
 * @file   RewritingVisitor.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Responsible for performing code rewriting of a YAGI program, e.g. pattern matching
 * gets rewritten into nested for-loops according to the specified YAGI semantics.
 */

/*
 This file is part of YAGI.

 YAGI is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3.0 of the License, or (at your option) any later version.

 YAGI is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with YAGI.
*/


#ifndef REWRITINGVISITOR_H_
#define REWRITINGVISITOR_H_

#include <memory>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include "../../utils/Any.h"
#include "../../common/ASTNodeVisitorBase.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionDecl.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionEffect.h"
#include "../../common/ASTNodeTypes/Statements/NodeForLoop.h"
#include "../../common/ASTNodeTypes/Statements/NodeBlock.h"
#include "../../common/ASTNodeTypes/Statements/NodeIDAssignment.h"
#include "../../common/ASTNodeTypes/ProgramStructure/NodeProgram.h"
#include "../../common/ASTNodeTypes/Statements/NodeProcExecution.h"
#include "../../common/ASTNodeTypes/Statements/NodeSitCalcActionExecution.h"
#include "ActionProcedureInterpretationVisitor.h"
#include "../Database/DatabaseManager.h"

using namespace yagi::database;

namespace yagi {
namespace execution {

/**
 * Visitor class responsible for performing code rewriting of a YAGI program
 */
class RewritingVisitor: public ASTNodeVisitorBase,
    public Visitor<NodeIDAssignment>,
    public Visitor<NodeActionDecl>,
    public Visitor<NodeActionEffect>,
    public Visitor<NodeSet>,
    public Visitor<NodeTuple>,
    public Visitor<NodePatternMatching>,
    public Visitor<NodeSetExpression>,
    public Visitor<NodeVariable>,
    public Visitor<NodeString>
{
  private:

    /**
     * Checks whether or not a tuples is a pattern matching tuple
     * @param tupleElements The tuple to check
     * @return True if tuple involves pattern matching, false otherwise
     */
    bool isPatternMatchingTuple(const std::vector<std::string>& tupleElements);

    /**
     * Performs the pattern matching rewriting
     * @param fluentName The name of the involved fluent
     * @param assOp The assignment operator
     * @param tuple The involved tuple
     * @return The for-loop resulting from the rewriting
     */
    std::shared_ptr<NodeForLoop> rewritePatternMatching(const std::string& fluentName,
        AssignmentOperator assOp, const std::vector<std::string>& tuple);

    /**
     * Unique identifier to identify pattern matching in a tuple
     */
    const std::string PATTERN_MATCH_ID;

  public:
    /**
     * Default ctor
     */
    RewritingVisitor();

    /**
     * Default dtor
     */
    virtual ~RewritingVisitor();

    /**
     * Visit method for action declaration
     * @param actionDecl The action decl. node
     * @return Nothing
     */
    Any visit(NodeActionDecl& actionDecl);

    /**
     * Visit method for action effect
     * @param effect The action effect node
     * @return Nothing
     */
    Any visit(NodeActionEffect& effect);

    /**
     * Visit method for YAGI ID assignment
     * @param idAssignment The assignment node
     * @return If pattern matching is involved the rewritten assignment, else nothing
     */
    Any visit(NodeIDAssignment& idAssignment);

    /**
     * Visit method for set
     * @param nodeSet The set node
     * @return The set of strings
     */
    Any visit(NodeSet& nodeSet);

    /**
     * Visit method for a YAGI tuple
     * @param nodeTuple The tuple node
     * @return The tuple values
     */
    Any visit(NodeTuple& nodeTuple);

    /**
     * Visit method for pattern matching
     * @param nodePatternMatching The pattern matching node
     * @return A unique string identifier for 'this is pattern matching'
     */
    Any visit(NodePatternMatching& nodePatternMatching);

    /**
     * Visit method for set expression
     * @param nodeSetExpr The set expression node
     * @return The LHS of the set expression
     */
    Any visit(NodeSetExpression& nodeSetExpr);

    /**
     * Visit method for a YAGI variable
     * @param variable The variable node
     * @return The name of the variable
     */
    Any visit(NodeVariable& variable);

    /**
     * Visit method for a YAGI string
     * @param nodeString The string node
     * @return The string value
     */
    Any visit(NodeString& nodeString);
};

}
/* namespace execution */
} /* namespace yagi */

#endif /* REWRITINGVISITOR_H_ */
