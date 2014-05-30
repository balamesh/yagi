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
  intNode->setValueFromString(intVal);

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
  opNode->fromString(op);

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
  //TODO
}

void ASTBuilder::addTuple()
{
  auto tuple = std::make_shared<NodeTuple>();
  ast.push_front(tuple);
}
void ASTBuilder::consumeTuple()
{
  //get tuple
  auto tuple = std::dynamic_pointer_cast<NodeTuple>(ast.front());
  ast.pop_front();

  //get set
  auto set = std::dynamic_pointer_cast<NodeSet>(ast.front());
  if (set == nullptr)
    throw std::runtime_error("No NodeSet for consumeTuple!");

  set->addTuple(tuple);
}
void ASTBuilder::consumeTupleVal()
{
  //get tuple val
  auto val = std::dynamic_pointer_cast<ASTNodeBase>(ast.front());
  ast.pop_front();

  //get tuple
  auto tuple = std::dynamic_pointer_cast<NodeTuple>(ast.front());
  if (tuple == nullptr)
    throw std::runtime_error("No NodeTuple for consumeTupleVal!");

  tuple->addTupleValue(val);
}
void ASTBuilder::addSet()
{
  auto set = std::make_shared<NodeSet>();
  ast.push_front(set);
}
void ASTBuilder::addSetExpr()
{
  auto setExpr = std::make_shared<NodeSetExpression>();

  auto rhs = std::dynamic_pointer_cast<ASTNodeBase>(ast.front());
  if (rhs == nullptr)
    throw std::runtime_error("No ASTNodeBase for SetExpr rhs!");
  ast.pop_front();

  auto lhs = std::dynamic_pointer_cast<ASTNodeBase>(ast.front());
  if (lhs == nullptr)
    throw std::runtime_error("No ASTNodeBase for SetExpr lhs!");
  ast.pop_front();

  auto op = std::dynamic_pointer_cast<NodeSetExpressionOperator>(ast.front());
  if (op == nullptr)
    throw std::runtime_error("No NodeSetExpressionOperator for SetExpr!");
  ast.pop_front();

  setExpr->setOperator(op);
  setExpr->setLhs(lhs);
  setExpr->setRhs(rhs);
  ast.push_front(setExpr);
}

void ASTBuilder::addFluentAssign(const std::string& fluentName)
{
  //get rhs of assignment
  auto rhs = std::dynamic_pointer_cast<ASTNodeBase>(ast.front());
  ast.pop_front();

  //build lhs
  auto fluentAss = std::make_shared<NodeFluentAssignment>();
  fluentAss->setFluentName(std::make_shared<NodeID>(fluentName));

  //get op
  auto assOp = std::dynamic_pointer_cast<NodeSetExpressionOperator>(
      ast.front());
  if (assOp == nullptr)
    throw std::runtime_error("No assignment operator for fluent assign!");
  ast.pop_front();

  fluentAss->setOperator(assOp);

  //if it's a "simple" assignment we need to create a setxpr,
  //otherwise it already has been created earlier...
  auto recursiveSetExpr = std::dynamic_pointer_cast<NodeSetExpression>(rhs);
  if (recursiveSetExpr == nullptr)
  {
    auto setExpr = std::make_shared<NodeSetExpression>();
    setExpr->setRhs(rhs); //in case it's a simple assignment we just set RHS and leave the rest nullptr
    fluentAss->setSetExpr(setExpr);
  }
  else
    fluentAss->setSetExpr(recursiveSetExpr);

  ast.push_front(fluentAss);
}

void ASTBuilder::addAssignmentOp(const std::string& op)
{
  auto opNode = std::make_shared<NodeSetExpressionOperator>();
  opNode->fromString(op);

  ast.push_front(opNode);
}

void ASTBuilder::addAtomConnective(const std::string& connective)
{
  auto conn = std::make_shared<NodeAtomConnective>();
  conn->fromString(connective);

  ast.push_front(conn);
}

void ASTBuilder::addFormulaConnective(const std::string& connective)
{
  auto conn = std::make_shared<NodeFormulaConnective>();
  conn->fromString(connective);

  ast.push_front(conn);
}

void ASTBuilder::addConstant(const std::string& constant)
{
  auto truthVal = std::make_shared<NodeConstant>();
  truthVal->fromString(constant);

  ast.push_front(truthVal);
}

void ASTBuilder::addAtom()
{
  //an atom can be just "true" or "false..
  auto elem = ast.front();

  if (std::dynamic_pointer_cast<NodeConstant>(elem) != nullptr)
  {
    //a truth value is a valid formula, i.e. we're done
    return;
  }

  //we have something of the form <connective> <expr> <expr> (right to left)
  //sanity check
  if ((std::dynamic_pointer_cast<NodeValueExpression>(elem) == nullptr)
      && (std::dynamic_pointer_cast<NodeSetExpression>(elem) == nullptr))
  {
    throw std::runtime_error("Atom rhs is neither value- nor setexpression!");
  }

  auto atom = std::make_shared<NodeAtom>();
  atom->setRightOperand(elem);
  ast.pop_front();

  auto leftOperand = ast.front();

  //sanity check
  if ((std::dynamic_pointer_cast<NodeValueExpression>(leftOperand) == nullptr)
      && (std::dynamic_pointer_cast<NodeSetExpression>(leftOperand) == nullptr))
  {
    throw std::runtime_error("Atom lhs is neither value- nor setexpression!");
  }

  ast.pop_front();
  atom->setLeftOperand(leftOperand);

  auto connective = std::dynamic_pointer_cast<NodeAtomConnective>(ast.front());
  if (connective == nullptr)
  {
    throw std::runtime_error("Atom connective is no NodeAtomConnective!");
  }

  ast.pop_front();
  atom->setConnective(connective);

  ast.push_front(atom);
}

void ASTBuilder::addNegation()
{
  //get formula to negate
  auto formula = std::dynamic_pointer_cast<NodeFormulaBase>(ast.front());
  ast.pop_front();

  if (formula == nullptr)
  {
    throw std::runtime_error("Want to negate something that's not a formula!");
  }

  auto formulaNegate = std::make_shared<NodeNegation>();
  formulaNegate->setFormula(formula);

  ast.push_front(formulaNegate);
}
void ASTBuilder::addConnectedFormula()
{
  //we have something of the form <formula_connective> <atom> <formula>
  //an atom can be just "true" or "false..
  auto rhs = std::dynamic_pointer_cast<NodeFormulaBase>(ast.front());

  //we have something of the form <connective> <expr> <expr> (right to left)
  //sanity check
  if (rhs == nullptr)
  {
    throw std::runtime_error("addConnectedFormula rhs is no NodeFormulaBase!");
  }

  auto compoundFormula = std::make_shared<NodeCompoundFormula>();
  compoundFormula->setRightOperand(rhs);
  ast.pop_front();

  auto lhs = std::dynamic_pointer_cast<NodeAtom>(ast.front());

  //sanity check
  if (lhs == nullptr)
  {
    throw std::runtime_error("Compound formula lhs is no atom!");
  }

  ast.pop_front();
  compoundFormula->setLeftOperand(lhs);

  auto connective = std::dynamic_pointer_cast<NodeFormulaConnective>(
      ast.front());
  if (connective == nullptr)
  {
    throw std::runtime_error("Atom connective is no NodeFormulaConnective!");
  }

  ast.pop_front();
  compoundFormula->setConnective(connective);

  ast.push_front(compoundFormula);

}
void ASTBuilder::addExists()
{
  addQuantifiedFormula(Quantifier::exists);
}
void ASTBuilder::addAll()
{
  addQuantifiedFormula(Quantifier::all);
}

void ASTBuilder::addQuantifiedFormula(Quantifier quant)
{
  auto quantifiedFormula = std::make_shared<NodeQuantifiedFormula>();
  quantifiedFormula->setQuantifier(quant);

  std::shared_ptr<NodeSetExpression> setExpr = nullptr;

  //we have something of the form <tuple> <setexpr> <formula>?
  auto formula = std::dynamic_pointer_cast<NodeFormulaBase>(ast.front());
  if (formula != nullptr) //formula is optional...
  {
    quantifiedFormula->setFormula(formula);
    ast.pop_front();
  }

  setExpr = std::dynamic_pointer_cast<NodeSetExpression>(ast.front());
  if (setExpr != nullptr)
  {
    throw std::runtime_error("Expected setexpr in quantified formula!");
  }

  quantifiedFormula->setSetExpr(setExpr);
  ast.pop_front();

  auto tuple = std::dynamic_pointer_cast<NodeTuple>(ast.front());

  //sanity check
  if (tuple == nullptr)
  {
    throw std::runtime_error("Expected tuple in quantified formula!");
  }

  ast.pop_front();
  quantifiedFormula->setTuple(tuple);

  ast.push_front(quantifiedFormula);
}

void ASTBuilder::addIn()
{
  auto inFormula = std::make_shared<NodeOperatorIn>();

  //we have something of the form <tuple> <setexpr>
  auto setExpr = std::dynamic_pointer_cast<NodeSetExpression>(ast.front());
  if (setExpr != nullptr)
  {
    throw std::runtime_error("Expected setexpr in in-formula!");
  }

  inFormula->setSetExpr(setExpr);
  ast.pop_front();

  auto tuple = std::dynamic_pointer_cast<NodeTuple>(ast.front());

  //sanity check
  if (tuple == nullptr)
  {
    throw std::runtime_error("Expected tuple in in-formula!");
  }

  ast.pop_front();
  inFormula->setTuple(tuple);

  ast.push_front(inFormula);
}

void ASTBuilder::addActionDeclNode(const std::string& actionName)
{

}
