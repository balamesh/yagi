/*
 * ToGologVisitor.h
 *
 *  Created on: May 23, 2014
 *      Author: cmaier
 */

#ifndef TOGOLOGVISITOR_H_
#define TOGOLOGVISITOR_H_

#include "../common/ASTNodeVisitorBase.h"
#include "../common/ASTNodeTypes/Domains/NodeDomainStringElements.h"
#include "../common/ASTNodeTypes/Declarations/FluentDecl/NodeFluentDecl.h"
#include "../common/ASTNodeTypes/Identifier/NodeID.h"
#include "../common/ASTNodeTypes/ProgramStructure/NodeProgram.h"
#include "../common/ASTNodeTypes/DataTypes/NodeString.h"
#include "../common/ASTNodeTypes/Domains/NodeDomainInteger.h"
#include "../common/ASTNodeTypes/Domains/NodeDomainString.h"
#include "../common/ASTNodeTypes/Declarations/FactDecl/NodeFactDecl.h"
#include "../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionDecl.h"
#include "../common/ASTNodeTypes/Formula/NodeAtom.h"
#include "../common/ASTNodeTypes/Formula/NodeAtomConnective.h"
#include "../common/ASTNodeTypes/Formula/NodeCompoundFormula.h"
#include "../common/ASTNodeTypes/Formula/NodeFormulaConnective.h"
#include "../common/ASTNodeTypes/Formula/NodeNegation.h"
#include "../common/ASTNodeTypes/Formula/NodeOperatorIn.h"
#include "../common/ASTNodeTypes/Formula/NodeQuantifiedFormula.h"
#include "../common/ASTNodeTypes/Formula/NodeConstant.h"
#include "../common/ASTNodeTypes/Variables/NodeVarList.h"
#include "../common/ASTNodeTypes/Declarations/ActionDecl/NodeSignal.h"
#include "../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionEffect.h"
#include "../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionPrecondition.h"

class ToGologVisitor: public ASTNodeVisitorBase
{
  private:
    std::vector<std::string> stringValues_;

  public:
    ToGologVisitor();
    virtual ~ToGologVisitor();

    virtual void visit(NodeDomainStringElements* domainStringElements) override;
    virtual void visit(NodeFluentDecl* fluentDecl) override;
    virtual void visit(NodeID* id) override;
    virtual void visit(NodeProgram* program) override;
    virtual void visit(NodeString* string) override;
    virtual void visit(NodeDomainInteger* domainInt) override;
    virtual void visit(NodeDomainString* domainString) override;

    virtual void visit(NodeFactDecl* factDecl) override;
    virtual void visit(NodeActionDecl* actionDecl) override;

    virtual void visit(NodeInteger* integer) override;
    virtual void visit(NodeValueExpression* expr) override;
    virtual void visit(NodeValueExpressionOperator* exprOp) override;
    virtual void visit(NodeVariableAssignment* ass) override;

    virtual void visit(NodeVariable* var) override;
    virtual void visit(NodeVarList* varList) override;

    virtual void visit(NodeSetExpressionOperator* ass) override;
    virtual void visit(NodeFluentAssignment* ass) override;
    virtual void visit(NodeSet* ass) override;
    virtual void visit(NodeSetExpression* ass) override;
    virtual void visit(NodeTuple* ass) override;

    virtual void visit(NodeAtom* atom) override;
    virtual void visit(NodeAtomConnective* atomConnective) override;
    virtual void visit(NodeCompoundFormula* compoundFormula) override;
    virtual void visit(NodeFormulaConnective* formulaConnective) override;
    virtual void visit(NodeNegation* negation) override;
    virtual void visit(NodeOperatorIn* operatorIn) override;
    virtual void visit(NodeQuantifiedFormula* quantifiedFormula) override;
    virtual void visit(NodeConstant* constant) override;
    virtual void visit(NodeSignal* signal) override;
    virtual void visit(NodeActionEffect* actionEffect) override;
    virtual void visit(NodeActionPrecondition* actionPrecondition) override;
};

#endif /* INTERPRETATIONVISITOR_H_ */
