/*
 * ASTBuilder.cpp
 *
 *  Created on: Apr 24, 2014
 *      Author: cmaier
 */

#include "ASTBuilder.h"
#include <assert.h>

ASTBuilder::ASTBuilder()
{
  // TODO Auto-generated constructor stub
}

ASTBuilder::~ASTBuilder()
{
  // TODO Auto-generated destructor stub
}

void ASTBuilder::addDomainElement(const std::string& domainElement)
{
  auto domain = std::static_pointer_cast<NodeDomainStringElements>(ast.back());
  auto stringNode = std::make_shared<NodeString>();
  stringNode->setString(domainElement);

  domain->addStringToDomain(stringNode);
}
void ASTBuilder::addDomainStringElementsNode()
{
  auto domainStringElements = std::make_shared<NodeDomainStringElements>();
  ast.push_back(domainStringElements);

}

void ASTBuilder::addDomainIntegerNode()
{
  auto domainInteger = std::make_shared<NodeDomainInteger>();
  ast.push_back(domainInteger);
}

void ASTBuilder::addDomainStringNode()
{
  auto domainString = std::make_shared<NodeDomainString>();
  ast.push_back(domainString);
}

void ASTBuilder::addProgram()
{
  auto programNode = std::make_shared<NodeProgram>();

  std::for_each(ast.begin(), ast.end(),
      [&programNode](std::shared_ptr<ASTNodeBase> statement)
      {
        programNode->addStatementToProgram(statement);
      });

  ast.clear();
  ast.push_back(programNode);
}

void ASTBuilder::addFluentDeclNode(const std::string& fluentName)
{
  auto fluentDeclNode = std::make_shared<NodeFluentDecl>();

  fluentDeclNode->setFluentName(std::make_shared<NodeID>(fluentName));

  auto firstNoDomain = std::find_if_not(std::begin(ast), std::end(ast),
      [](std::shared_ptr<ASTNodeBase> elem)
      { return dynamic_cast<NodeDomainBase*>(elem.get());});

  if (firstNoDomain != std::end(ast))
  {
    std::for_each(std::begin(ast), firstNoDomain - 1,
        [&fluentDeclNode](std::shared_ptr<ASTNodeBase> elem)
        { fluentDeclNode->addDomain(std::static_pointer_cast<NodeDomainBase>(elem));});

    ast.erase(std::begin(ast), firstNoDomain - 1);
  }

  ast.push_front(fluentDeclNode);
}

void ASTBuilder::addFactDeclNode(const std::string& factName)
{
  auto factDeclNode = std::make_shared<NodeFactDecl>();

  factDeclNode->setFactName(std::make_shared<NodeID>(factName));

  auto firstNoDomain = std::find_if_not(std::begin(ast), std::end(ast),
      [](std::shared_ptr<ASTNodeBase> elem)
      { return dynamic_cast<NodeDomainBase*>(elem.get());});

  if (firstNoDomain != std::end(ast))
  {
    std::for_each(std::begin(ast), firstNoDomain - 1,
        [&factDeclNode](std::shared_ptr<ASTNodeBase> elem)
        { factDeclNode->addDomain(std::static_pointer_cast<NodeDomainBase>(elem));});

    ast.erase(std::begin(ast), firstNoDomain - 1);
  }

  ast.push_front(factDeclNode);
}

void ASTBuilder::addVarNode(const std::string& varName)
{

}

void ASTBuilder::addVarListNode()
{

}

void ASTBuilder::addActionDeclNode(const std::string& actionName)
{

}
