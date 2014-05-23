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
  outString += "DOMAIN ";
}

void ToStringVisitor::visit(NodeFluentDecl* fluentDecl)
{
  outString += "FLUENT_DECL ";
}

void ToStringVisitor::visit(NodeFactDecl* factDecl)
{
  outString += "FACT_DECL ";
}

void ToStringVisitor::visit(NodeActionDecl* actionDecl)
{
  outString += "ACTION_DECL ";
}

void ToStringVisitor::visit(NodeID* id)
{
  outString += "[ID=" + id->getId() + "] ";
}

void ToStringVisitor::visit(NodeProgram* program)
{
  std::cout << outString << std::endl;
}

void ToStringVisitor::visit(NodeDomainInteger* domainInt)
{
  outString += "DOMAIN_INTEGER ";
}

void ToStringVisitor::visit(NodeDomainString* domainString)
{
  outString += "DOMAIN_STRING ";
}
