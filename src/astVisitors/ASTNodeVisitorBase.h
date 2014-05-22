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

class ASTNodeVisitorBase
{
  public:
    ASTNodeVisitorBase() {};
    virtual ~ASTNodeVisitorBase() {};

    virtual void visit(NodeDomainStringElements* domainStringElements) = 0;
    virtual void visit(NodeFluentDecl* fluentDecl) = 0;
    virtual void visit(NodeID* id) = 0;
    virtual void visit(NodeProgram* program) = 0;
    virtual void visit(NodeString* string) = 0;
};

#endif /* ASTNODEVISITORBASE_H_ */
