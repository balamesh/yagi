/*
 * ASTBuilder.cpp
 *
 *  Created on: Apr 24, 2014
 *      Author: cmaier
 */

#include "ASTBuilder.h"

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
  auto domain = std::dynamic_pointer_cast<NodeDomainStringElements>(ast.back());
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
  auto fluent = std::dynamic_pointer_cast<NodeFluentDecl>(ast.front());
  auto fact = std::dynamic_pointer_cast<NodeFactDecl>(ast.front());

  if (fluent == nullptr && fact == nullptr)
    throw std::runtime_error("consumeDomain needs fluent or fact!");

  ast.pop_front();

  auto domain = std::dynamic_pointer_cast<NodeDomainBase>(ast.front());
  if (domain == nullptr)
    throw std::runtime_error("consumeDomain needs domain!");

  ast.pop_front();

  if (fluent != nullptr)
  {
    fluent->addDomain(domain);
    ast.push_front(fluent);
  }
  else
  {
    fact->addDomain(domain);
    ast.push_front(fact);
  }
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
  ast.push_front(fluentDeclNode);
}

void ASTBuilder::addFactDeclNode(const std::string& factName)
{
  auto factDeclNode = std::make_shared<NodeFactDecl>();
  factDeclNode->setFactName(std::make_shared<NodeID>(factName));

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

  auto rhs = std::dynamic_pointer_cast<ASTNodeBase>(ast.front());
  if (rhs == nullptr)
    throw std::runtime_error("No ASTNodeBase for ValExpr rhs!");
  ast.pop_front();

  auto lhs = std::dynamic_pointer_cast<ASTNodeBase>(ast.front());
  if (lhs == nullptr)
    throw std::runtime_error("No ASTNodeBase for ValExpr lhs!");
  ast.pop_front();

  auto op = std::dynamic_pointer_cast<NodeValueExpressionOperator>(ast.front());
  if (op == nullptr)
    throw std::runtime_error("No NodeValueExpressionOperator for ValExpr!");
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
  //get rhs of assignment
  auto rhs = std::dynamic_pointer_cast<ASTNodeBase>(ast.front());
  ast.pop_front();

  //get var
  auto var = std::dynamic_pointer_cast<NodeVariable>(ast.front());
  if (var == nullptr)
    throw std::runtime_error("No NodeVariable for VarAssign!");
  ast.pop_front();

  auto varAss = std::make_shared<NodeVariableAssignment>();
  varAss->setVariable(var);

  //if it's a "simple" assignment we need to create a valexpr,
  //otherwise it already has been created earlier...
  auto recursiveValExpr = std::dynamic_pointer_cast<NodeValueExpression>(rhs);
  if (recursiveValExpr == nullptr)
  {
    auto valExpr = std::make_shared<NodeValueExpression>();
    valExpr->setRhs(rhs); //in case it's a simple assignment we just set RHS and leave the rest nullptr
    varAss->setValExpr(valExpr);
  }
  else
    varAss->setValExpr(recursiveValExpr);

  ast.push_front(varAss);

}

void ASTBuilder::addPatternMatch()
{
}
void ASTBuilder::addTuple()
{
}
void ASTBuilder::consumeTuple()
{
}
void ASTBuilder::consumeTupleVal()
{
}
void ASTBuilder::addSet()
{
}
void ASTBuilder::addSetExpr()
{
}

void ASTBuilder::addFluentAssign(const std::string& fluentName)
{

}

void ASTBuilder::addAssignmentOp(const std::string& op)
{

}

void ASTBuilder::addActionDeclNode(const std::string& actionName)
{

}
