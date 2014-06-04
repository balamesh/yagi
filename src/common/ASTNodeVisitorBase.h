/*
 * ASTNodeVisitorBase.h
 *
 *  Created on: May 22, 2014
 *      Author: cmaier
 */

#ifndef ASTNODEVISITORBASE_H_
#define ASTNODEVISITORBASE_H_

class NodeDomainStringElements;
class NodeFluentDecl;
class NodeID;
class NodeProgram;
class NodeString;
class NodeDomainString;
class NodeDomainInteger;
class NodeFactDecl;
class NodeActionDecl;
class NodeVariableAssignment;
class NodeValueExpression;
class NodeValueExpressionOperator;
class NodeInteger;
class NodeVariable;
class NodeSetExpressionOperator;
class NodeFluentAssignment;
class NodeSet;
class NodeSetExpression;
class NodeTuple;
class NodeActionEffect;
class NodeActionPrecondition;
class NodeAtom;
class NodeAtomConnective;
class NodeCompoundFormula;
class NodeFormulaConnective;
class NodeNegation;
class NodeOperatorIn;
class NodeQuantifiedFormula;
class NodeSignal;
class NodeConstant;
class NodeVarList;

class NodeActiveSensing;
class NodeForLoopAssignment;
class NodeConditionalAssignment;
class NodePassiveSensingDecl;

class ASTNodeVisitorBase
{
  public:
    ASTNodeVisitorBase()
    {
    }
    ;
    virtual ~ASTNodeVisitorBase()
    {
    }
    ;

    //Program Structure
    virtual void visit(NodeProgram* program) = 0;

    //Fluents and facts
    virtual void visit(NodeFluentDecl* fluentDecl) = 0;
    virtual void visit(NodeFactDecl* factDecl) = 0;
    virtual void visit(NodePassiveSensingDecl* passiveSensingDecl) = 0;

    //Action Decl
    virtual void visit(NodeActionDecl* actionDecl) = 0;
    virtual void visit(NodeSignal* signal) = 0;
    virtual void visit(NodeActionEffect* actionEffect) = 0;
    virtual void visit(NodeActionPrecondition* actionPrecondition) = 0;
    virtual void visit(NodeActiveSensing* activeSensing) = 0;

    //Domains
    virtual void visit(NodeDomainStringElements* domainStringElements) = 0;
    virtual void visit(NodeDomainInteger* domainInt) = 0;
    virtual void visit(NodeDomainString* domainString) = 0;

    //Identifier
    virtual void visit(NodeID* id) = 0;

    //Variables
    virtual void visit(NodeVariable* var) = 0;
    virtual void visit(NodeVarList* varList) = 0;

    //Expressions
    virtual void visit(NodeValueExpression* expr) = 0;
    virtual void visit(NodeValueExpressionOperator* exprOp) = 0;

    //Data Types
    virtual void visit(NodeString* string) = 0;
    virtual void visit(NodeInteger* integer) = 0;

    //Assignments
    virtual void visit(NodeVariableAssignment* ass) = 0;
    virtual void visit(NodeForLoopAssignment* ass) = 0;
    virtual void visit(NodeConditionalAssignment* ass) = 0;

    virtual void visit(NodeSetExpressionOperator* ass) = 0;
    virtual void visit(NodeFluentAssignment* ass) = 0;
    virtual void visit(NodeSet* ass) = 0;
    virtual void visit(NodeSetExpression* ass) = 0;
    virtual void visit(NodeTuple* ass) = 0;

    //Formulas
    virtual void visit(NodeAtom* atom) = 0;
    virtual void visit(NodeAtomConnective* atomConnective) = 0;
    virtual void visit(NodeCompoundFormula* compoundFormula) = 0;
    virtual void visit(NodeFormulaConnective* formulaConnective) = 0;
    virtual void visit(NodeNegation* negation) = 0;
    virtual void visit(NodeOperatorIn* operatorIn) = 0;
    virtual void visit(NodeQuantifiedFormula* quantifiedFormula) = 0;
    virtual void visit(NodeConstant* constant) = 0;
};

#endif /* ASTNODEVISITORBASE_H_ */
