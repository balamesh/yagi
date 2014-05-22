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
//  auto domainElements = domainStringElements->getDomainElements();
//  auto ret = std::accumulate(std::begin(domainElements),
//      std::end(domainElements), std::string { "{" },
//      [](std::string& first, const std::string& last)
//      { return first + last + ",";});
//
//  ret.pop_back();
//  ret += "}";
//
//  outString += ret;

  outString += "<= DOMAIN ";
}

void ToStringVisitor::visit(NodeFluentDecl* fluentDecl)
{
//  auto fluentName = fluentDecl->getFluentName();
//  auto domain = fluentDecl->getDomain();
//
//  outString += std::string(
//      std::string("Fluent '") + fluentName + "' Domain: "
//          + domain);

  outString += "<= FLUENT_DECL ";
}

void ToStringVisitor::visit(NodeID* id)
{
  outString += "[ID=" + id->getId() + "] ";
}

void ToStringVisitor::visit(NodeProgram* program)
{
  std::cout << outString << std::endl;
}
