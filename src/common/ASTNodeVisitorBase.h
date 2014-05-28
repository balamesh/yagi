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

    //Declarations
    virtual void visit(NodeFluentDecl* fluentDecl) = 0;
    virtual void visit(NodeFactDecl* factDecl) = 0;
    virtual void visit(NodeActionDecl* actionDecl) = 0;

    //Domains
    virtual void visit(NodeDomainStringElements* domainStringElements) = 0;
    virtual void visit(NodeDomainInteger* domainInt) = 0;
    virtual void visit(NodeDomainString* domainString) = 0;

    //Identifier
    virtual void visit(NodeID* id) = 0;

    //Variables
    virtual void visit(NodeVariable* var) = 0;

    //Expressions
    virtual void visit(NodeValueExpression* expr) = 0;
    virtual void visit(NodeValueExpressionOperator* exprOp) = 0;

    //Data Types
    virtual void visit(NodeString* string) = 0;
    virtual void visit(NodeInteger* integer) = 0;

    //Assignments
    virtual void visit(NodeVariableAssignment* ass) = 0;

    virtual void visit(NodeSetExpressionOperator* ass) = 0;
    virtual void visit(NodeFluentAssignment* ass) = 0;
    virtual void visit(NodeSet* ass) = 0;
    virtual void visit(NodeSetExpression* ass) = 0;
    virtual void visit(NodeTuple* ass) = 0;
};

#endif /* ASTNODEVISITORBASE_H_ */
