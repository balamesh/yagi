/*
 * ToStringVisitor.cpp
 *
 *  Created on: May 22, 2014
 *      Author: cmaier
 */

#include "ToStringVisitor.h"

#include <algorithm>

ToStringVisitor::ToStringVisitor()
{
  // TODO Auto-generated constructor stub

}

ToStringVisitor::~ToStringVisitor()
{
  // TODO Auto-generated destructor stub
}

void ToStringVisitor::visit(NodeString* string)
{
  outString += "[STRING=" + string->getString() + "] ";
}

void ToStringVisitor::visit(NodeDomainStringElements* domainStringElements)
{
  outString += "[DomainRoot] ";
}

void ToStringVisitor::visit(NodeFluentDecl* fluentDecl)
{
  outString += "[FluentDecl] ";
}

void ToStringVisitor::visit(NodeFactDecl* factDecl)
{
  outString += "[FactDecl] ";
}

void ToStringVisitor::visit(NodeActionDecl* actionDecl)
{
  //std::cout << "[ActionDecl]" << std::endl;
}

void ToStringVisitor::visit(NodeID* id)
{
  outString += "[ID=" + id->getId() + "] ";
}

void ToStringVisitor::visit(NodeProgram* program)
{
  std::cout << "--Program--" << std::endl;
  std::cout << outString << std::endl;
}

void ToStringVisitor::visit(NodeDomainInteger* domainInt)
{
  outString += "[DomainInteger] ";
}

void ToStringVisitor::visit(NodeDomainString* domainString)
{
  outString += "[DomainString] ";
}

void ToStringVisitor::visit(NodeInteger* integer)
{
  outString += "[Integer=" + std::to_string(integer->getValue()) + "] ";
}
void ToStringVisitor::visit(NodeValueExpression* expr)
{
  outString += "[ValueExpression] ";
}
void ToStringVisitor::visit(NodeValueExpressionOperator* exprOp)
{
  outString += std::string{"[ExprOp="}
      + (exprOp->getOperator() == ValueExprOperator::Plus ? "+" : "-") + "] ";
}
void ToStringVisitor::visit(NodeVariableAssignment* ass)
{
  outString += "[VariableAss] ";
}

void ToStringVisitor::visit(NodeVariable* var)
{
  outString += "[Var=" + var->getVarName() + "] ";
}
