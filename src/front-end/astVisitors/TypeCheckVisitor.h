/**
 * @file   TypeCheckVisitor.h
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * Performs typechecking on the AST of the YAGI program.
 * !!Typechecking is still very rudimentary, i.e. very little type checking is performed!!
 */

#ifndef TYPECHECKVISITOR_H_
#define TYPECHECKVISITOR_H_

#include <vector>
#include <algorithm>

#include "../../common/ASTNodeVisitorBase.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainStringElements.h"
#include "../../common/ASTNodeTypes/Declarations/FluentDecl/NodeFluentDecl.h"
#include "../../common/ASTNodeTypes/Identifier/NodeID.h"
#include "../../common/ASTNodeTypes/ProgramStructure/NodeProgram.h"
#include "../../common/ASTNodeTypes/DataTypes/NodeString.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionDecl.h"
#include "../../common/ASTNodeTypes/Declarations/ExogenousEventDecl/NodeExogenousEventDecl.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainString.h"
#include "../../common/ASTNodeTypes/Declarations/FactDecl/NodeFactDecl.h"
#include "../../common/ASTNodeTypes/Declarations/ProcDecl/NodeProcDecl.h"
#include "../../common/ASTNodeTypes/Statements/NodeIDAssignment.h"

using namespace yagi::container;

/**
 * Performs typechecking on the AST of the YAGI program.
 * !!This class is still very rudimentary, i.e. very little type checking is performed!!
 */
class TypeCheckVisitor: public ASTNodeVisitorBase, public Visitor<NodeIDAssignment>, public Visitor<
    NodeActionDecl>, public Visitor<NodeProcDecl>, public Visitor<NodeExogenousEventDecl>
{
  private:
    /**
     * Flag if type checking error occurred
     */
    bool hasTypeError_ = false;

    /**
     * Collection of error texts for diagnostics
     */
    std::vector<std::string> errorTexts_;

    /**
     * Flag if type warnings occurred
     */
    bool hasWarnings_ = false;

    /**
     * Collection of warning texts for diagnostics.
     */
    std::vector<std::string> warningTexts_;
  public:

    /**
     * Default ctor
     */
    TypeCheckVisitor();

    /**
     * Visit method for IDAssignment
     * @param nodeIDAssignment AST node
     * @return Diagnostics data - if needed
     */
    Any visit(NodeIDAssignment& nodeIDAssignment);

    /**
     * Visit method for action decl
     * @param nodeActionDecl AST node
     * @return Diagnostics data - if needed
     */
    Any visit(NodeActionDecl& nodeActionDecl);

    /**
     * Visit method for proc decl
     * @param nodeProcDecl AST node
     * @return Diagnostics data - if needed
     */
    Any visit(NodeProcDecl& nodeProcDecl);

    /**
     * Visit method for exo event decl
     * @param nodeExoEventDecl AST node
     * @return Diagnostics data - if needed
     */
    Any visit(NodeExogenousEventDecl& nodeExoEventDecl);

    /**
     * Getter for error texts
     * @return The error texts
     */
    const std::vector<std::string>& getErrorTexts() const
    {
      return errorTexts_;
    }

    /**
     * Getter for type error flag
     * @return True if type error occurred, false otherwise
     */
    bool hasTypeError() const
    {
      return hasTypeError_;
    }

    /**
     * Getter for warnings flag
     * @return True if warnings occurred, false otherwise
     */
    bool hasWarnings() const
    {
      return hasWarnings_;
    }

    /**
     * Getter for warning texts
     * @return Collection of warning texts
     */
    const std::vector<std::string>& getWarningTexts() const
    {
      return warningTexts_;
    }
};

#endif /* TYPECHECKVISITOR_H_ */
