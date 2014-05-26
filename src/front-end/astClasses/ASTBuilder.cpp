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

void ASTBuilder::consumeDomain()
{
  //TODO: can be either fluent or fact
  auto fluent = std::static_pointer_cast<NodeFluentDecl>(ast.front());
  if (fluent == nullptr)
    throw std::runtime_error("consumeDomain needs fluent or fact!");
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

  //std::cout << "bla!" << std::endl;

//  auto firstNoDomain = std::find_if_not(std::begin(ast), std::end(ast),
//      [](std::shared_ptr<ASTNodeBase> elem)
//      { return dynamic_cast<NodeDomainBase*>(elem.get());});
//
//  if (firstNoDomain != std::end(ast))
//  {
//    std::for_each(std::begin(ast), firstNoDomain - 1,
//        [&fluentDeclNode](std::shared_ptr<ASTNodeBase> elem)
//        { fluentDeclNode->addDomain(std::static_pointer_cast<NodeDomainBase>(elem));});
//
//    ast.erase(std::begin(ast), firstNoDomain - 1);
//  }

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
  auto varNode = std::make_shared<NodeVariable>();
  varNode->setVarName(varName);

  ast.push_front(varNode);
}

void ASTBuilder::addVarListNode()
{

}

void ASTBuilder::addIntNode(const std::string& intVal)
{
  auto intNode = std::make_shared<NodeInteger>();
  intNode->setValueFromString(intVal); //TODO: can go boom!

  ast.push_front(intNode);
}

void ASTBuilder::addStringNode(const std::string& stringVal)
{
  auto stringNode = std::make_shared<NodeString>();
  stringNode->setString(stringVal);

  ast.push_front(stringNode);
}

void ASTBuilder::addValueExpressionNode()
{
  auto valExpr = std::make_shared<NodeValueExpression>();

  //get operator, lhs and rhs (in that order)
  auto op = std::static_pointer_cast<NodeValueExpressionOperator>(ast.front());
  if (op == nullptr)
    throw std::runtime_error("No NodeValueExpressionOperator for ValExpr!");
  ast.pop_front();

  auto lhs = std::static_pointer_cast<NodeValueExpression>(ast.front());
  if (op == nullptr)
    throw std::runtime_error("No NodeValueExpression for ValExpr lhs!");
  ast.pop_front();

  auto rhs = std::static_pointer_cast<NodeValueExpression>(ast.front());
  if (op == nullptr)
    throw std::runtime_error("No NodeValueExpression for ValExpr rhs!");
  ast.pop_front();

  valExpr->setOperator(op);
  valExpr->setLhs(lhs);
  valExpr->setRhs(rhs);
  ast.push_front(valExpr);

}

void ASTBuilder::addExprOperator(const std::string& op)
{
  auto opNode = std::make_shared<NodeValueExpressionOperator>();
  opNode->fromString(op); //TODO: Can go boom!

  ast.push_front(opNode);
}

void ASTBuilder::addVarAssign()
{
  auto varAss = std::make_shared<NodeVariableAssignment>();

  //get var and valexpr
  auto var = std::static_pointer_cast<NodeVariable>(ast.front());
  if (var == nullptr)
    throw std::runtime_error("No NodeVariable for VarAssign!");
  ast.pop_front();

  auto valExpr = std::static_pointer_cast<NodeValueExpression>(ast.front());
  if (valExpr == nullptr)
    throw std::runtime_error("No ValExpr for VarAssign!");
  ast.pop_front();

  varAss->setVariable(var);
  varAss->setValExpr(valExpr);
  ast.push_front(varAss);

}

void ASTBuilder::addActionDeclNode(const std::string& actionName)
{

}
