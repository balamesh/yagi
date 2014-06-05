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

void ASTBuilder::addDomainStringElementsNode()
{
  auto domainStringElements = std::make_shared<NodeDomainStringElements>();
  ast.push(domainStringElements);
}

void ASTBuilder::addDomainIntegerNode()
{
  auto domainInteger = std::make_shared<NodeDomainInteger>();
  ast.push(domainInteger);
}

void ASTBuilder::addDomainStringNode()
{
  auto domainString = std::make_shared<NodeDomainString>();
  ast.push(domainString);
}

void ASTBuilder::addDomainElement(const std::string& domainElement)
{
  auto domain = getFrontElement<NodeDomainStringElements>();
  auto stringNode = std::make_shared<NodeString>();
  stringNode->setString(domainElement);

  domain->addStringToDomain(stringNode);
}

void ASTBuilder::consumeDomain()
{
  auto domain = getFrontElement<NodeDomainBase>();
  if (domain == nullptr)
    throw std::runtime_error("consumeDomain needs domain!");

  ast.pop();

  auto fluent = getFrontElement<NodeFluentDecl>();
  auto fact = getFrontElement<NodeFactDecl>();

  if (fluent == nullptr && fact == nullptr)
    throw std::runtime_error("consumeDomain needs fluent or fact!");

  ast.pop();

  if (fluent != nullptr)
  {
    fluent->addDomain(domain);
    ast.push(fluent);
  }
  else
  {
    fact->addDomain(domain);
    ast.push(fact);
  }
}

void ASTBuilder::addID(const std::string& id)
{
  auto idNode = std::make_shared<NodeID>(id);
  ast.push(idNode);
}

void ASTBuilder::addProgram()
{
  auto programNode = std::make_shared<NodeProgram>();

  while (!ast.empty())
  {
    programNode->addStatementToProgram(ast.top());
    ast.pop();
  }

  ast.push(programNode);
}

void ASTBuilder::addFluentDeclNode(const std::string& fluentName)
{
  auto fluentDeclNode = std::make_shared<NodeFluentDecl>();

  fluentDeclNode->setFluentName(std::make_shared<NodeID>(fluentName));
  ast.push(fluentDeclNode);
}

void ASTBuilder::addPassiveSensingDeclNode(const std::string& passSensName)
{
  auto passiveSensingNode = std::make_shared<NodePassiveSensingDecl>();
  passiveSensingNode->setPassiveSensingName(std::make_shared<NodeID>(passSensName));

  //there must be a varlist for passive sensing
  auto varList = getFrontElement<NodeVarList>();
  if (varList == nullptr)
  {
    throw std::runtime_error("There must be a varlist for passive sensing, but there isn't!");
  }
  passiveSensingNode->setArgList(varList);
  ast.pop();

  ast.push(passiveSensingNode);
}

void ASTBuilder::addFactDeclNode(const std::string& factName)
{
  auto factDeclNode = std::make_shared<NodeFactDecl>();
  factDeclNode->setFactName(std::make_shared<NodeID>(factName));

  ast.push(factDeclNode);
}

void ASTBuilder::addVarNode(const std::string& varName)
{
  auto varNode = std::make_shared<NodeVariable>();
  varNode->setVarName(varName);

  ast.push(varNode);
}

void ASTBuilder::addVarListNode()
{
  auto varList = std::make_shared<NodeVarList>();
  ast.push(varList);
}

void ASTBuilder::addIntNode(const std::string& intVal)
{
  auto intNode = std::make_shared<NodeInteger>();
  intNode->setValueFromString(intVal);

  ast.push(intNode);
}

void ASTBuilder::addStringNode(const std::string& stringVal)
{
  auto stringNode = std::make_shared<NodeString>();
  stringNode->setString(stringVal);

  ast.push(stringNode);
}

void ASTBuilder::addValueExpressionNode()
{
  auto valExpr = std::make_shared<NodeValueExpression>();

  auto rhs = getFrontElement<ASTNodeBase>();
  if (rhs == nullptr)
    throw std::runtime_error("No ASTNodeBase for ValExpr rhs!");
  ast.pop();

  auto lhs = getFrontElement<ASTNodeBase>();
  if (lhs == nullptr)
    throw std::runtime_error("No ASTNodeBase for ValExpr lhs!");
  ast.pop();

  auto op = getFrontElement<NodeValueExpressionOperator>();
  if (op == nullptr)
    throw std::runtime_error("No NodeValueExpressionOperator for ValExpr!");
  ast.pop();

  valExpr->setOperator(op);
  valExpr->setLhs(lhs);
  valExpr->setRhs(rhs);
  ast.push(valExpr);
}

void ASTBuilder::addExprOperator(const std::string& op)
{
  auto opNode = std::make_shared<NodeValueExpressionOperator>();
  opNode->fromString(op);

  ast.push(opNode);
}

void ASTBuilder::addVarAssign()
{
  //get rhs of assignment
  auto rhs = getFrontElement<ASTNodeBase>();
  ast.pop();

  //get var
  auto var = getFrontElement<NodeVariable>();
  if (var == nullptr)
    throw std::runtime_error("No NodeVariable for VarAssign!");
  ast.pop();

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

  ast.push(varAss);

}

void ASTBuilder::addPatternMatch()
{
  auto patternMatching = std::make_shared<NodePatternMatching>();
  ast.push(patternMatching);
}

void ASTBuilder::addTuple()
{
  auto tuple = std::make_shared<NodeTuple>();
  ast.push(tuple);
}
void ASTBuilder::consumeTuple()
{
  //get tuple
  auto tuple = getFrontElement<NodeTuple>();
  ast.pop();

  //get set
  auto set = getFrontElement<NodeSet>();
  if (set == nullptr)
    throw std::runtime_error("No NodeSet for consumeTuple!");

  set->addTuple(tuple);
}
void ASTBuilder::consumeTupleVal()
{
  //get tuple val
  auto val = getFrontElement<ASTNodeBase>();
  ast.pop();

  //get tuple
  auto tuple = getFrontElement<NodeTuple>();
  if (tuple == nullptr)
    throw std::runtime_error("No NodeTuple for consumeTupleVal!");

  tuple->addTupleValue(val);
}
void ASTBuilder::addSet()
{
  auto set = std::make_shared<NodeSet>();
  ast.push(set);
}
void ASTBuilder::addSetExpr()
{
  auto setExpr = std::make_shared<NodeSetExpression>();

  auto rhs = getFrontElement<ASTNodeBase>();
  if (rhs == nullptr)
    throw std::runtime_error("No ASTNodeBase for SetExpr rhs!");
  ast.pop();

  auto lhs = getFrontElement<ASTNodeBase>();
  if (lhs == nullptr)
    throw std::runtime_error("No ASTNodeBase for SetExpr lhs!");
  ast.pop();

  auto op = getFrontElement<NodeSetExpressionOperator>();
  if (op == nullptr)
    throw std::runtime_error("No NodeSetExpressionOperator for SetExpr!");
  ast.pop();

  setExpr->setOperator(op);
  setExpr->setLhs(lhs);
  setExpr->setRhs(rhs);
  ast.push(setExpr);
}

void ASTBuilder::addFluentAssign(const std::string& fluentName)
{
  //get rhs of assignment
  auto rhs = getFrontElement<ASTNodeBase>();
  ast.pop();

  //build lhs
  auto fluentAss = std::make_shared<NodeFluentAssignment>();
  fluentAss->setFluentName(std::make_shared<NodeID>(fluentName));

  //get op
  auto assOp = getFrontElement<NodeSetExpressionOperator>();
  if (assOp == nullptr)
    throw std::runtime_error("No assignment operator for fluent assign!");
  ast.pop();

  fluentAss->setOperator(assOp);

  //TODO: should be created in everycase the <setexpr> rule gets executed!
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

  ast.push(fluentAss);
}

void ASTBuilder::addAssignmentOp(const std::string& op)
{
  auto opNode = std::make_shared<NodeSetExpressionOperator>();
  opNode->fromString(op);

  ast.push(opNode);
}

void ASTBuilder::addAtomConnective(const std::string& connective)
{
  auto conn = std::make_shared<NodeAtomConnective>();
  conn->fromString(connective);

  ast.push(conn);
}

void ASTBuilder::addFormulaConnective(const std::string& connective)
{
  auto conn = std::make_shared<NodeFormulaConnective>();
  conn->fromString(connective);

  ast.push(conn);
}

void ASTBuilder::addConstant(const std::string& constant)
{
  auto truthVal = std::make_shared<NodeConstant>();
  truthVal->fromString(constant);

  ast.push(truthVal);
}

void ASTBuilder::addAtom()
{
  //an atom can be just "true" or "false..
  auto elem = getFrontElement<ASTNodeBase>();

  if (std::dynamic_pointer_cast<NodeConstant>(elem) != nullptr)
  {
    //a truth value is a valid formula, i.e. we're done
    return;
  }

  auto atom = std::make_shared<NodeAtom>();

  //we have something of the form <connective> <expr> <expr> (right to left)
  //sanity check
  if ((std::dynamic_pointer_cast<NodeValueExpression>(elem) == nullptr)
      && (std::dynamic_pointer_cast<NodeSetExpression>(elem) == nullptr))
  {
    //try to make it a valexpr/setexpr
    if (NodeValueExpression::isPassedTypeValid(elem))
    {
      auto valExpr = std::make_shared<NodeValueExpression>();
      valExpr->setLhs(elem);
      atom->setRightOperand(valExpr);
    }
    else if (NodeSetExpression::isPassedTypeValid(elem))
    {
      auto setExpr = std::make_shared<NodeSetExpression>();
      setExpr->setLhs(elem);
      atom->setRightOperand(setExpr);
    }
    else
      throw std::runtime_error("Atom rhs is neither value- nor setexpression!");
  }
  else
    atom->setRightOperand(elem);

  ast.pop();
  auto leftOperand = getFrontElement<ASTNodeBase>();

  //sanity check
  //TODO: needs refactoring!
  if ((std::dynamic_pointer_cast<NodeValueExpression>(leftOperand) == nullptr)
      && (std::dynamic_pointer_cast<NodeSetExpression>(leftOperand) == nullptr))
  {
    //sanity check
    if (NodeValueExpression::isPassedTypeValid(leftOperand))
    {
      auto valExpr = std::make_shared<NodeValueExpression>();
      valExpr->setLhs(leftOperand);
      atom->setLeftOperand(valExpr);
    }
    else if (NodeSetExpression::isPassedTypeValid(leftOperand))
    {
      auto setExpr = std::make_shared<NodeSetExpression>();
      setExpr->setLhs(leftOperand);
      atom->setLeftOperand(setExpr);
    }
    else
      throw std::runtime_error("Atom rhs is neither value- nor setexpression!");
  }
  else
    atom->setLeftOperand(leftOperand);

  ast.pop();

  auto connective = getFrontElement<NodeAtomConnective>();
  if (connective == nullptr)
  {
    throw std::runtime_error("Atom connective is no NodeAtomConnective!");
  }

  ast.pop();
  atom->setConnective(connective);

  ast.push(atom);
}

void ASTBuilder::addNegation()
{
  //get formula to negate
  auto formula = getFrontElement<NodeFormulaBase>();
  ast.pop();

  if (formula == nullptr)
  {
    throw std::runtime_error("Want to negate something that's not a formula!");
  }

  auto formulaNegate = std::make_shared<NodeNegation>();
  formulaNegate->setFormula(formula);

  ast.push(formulaNegate);
}
void ASTBuilder::addConnectedFormula()
{
  //we have something of the form <formula_connective> <atom> <formula>
  //an atom can be just "true" or "false..
  auto rhs = getFrontElement<NodeFormulaBase>();

  //sanity check
  if (rhs == nullptr)
  {
    throw std::runtime_error("addConnectedFormula rhs is no NodeFormulaBase!");
  }

  auto compoundFormula = std::make_shared<NodeCompoundFormula>();
  compoundFormula->setRightOperand(rhs);
  ast.pop();

  auto lhs_atom = getFrontElement<NodeAtom>();
  auto lhs_constant = getFrontElement<NodeConstant>();

  //sanity check
  if (lhs_atom == nullptr && lhs_constant == nullptr)
  {
    throw std::runtime_error("Compound formula lhs is neither an atom nor a constant!");
  }

  compoundFormula->setLeftOperand(getFrontElement<NodeFormulaBase>());
  ast.pop();

  auto connective = getFrontElement<NodeFormulaConnective>();
  if (connective == nullptr)
  {
    throw std::runtime_error("Atom connective is no NodeFormulaConnective!");
  }

  ast.pop();
  compoundFormula->setConnective(connective);

  ast.push(compoundFormula);

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
  auto formula = getFrontElement<NodeFormulaBase>();
  if (formula != nullptr) //formula is optional...
  {
    quantifiedFormula->setFormula(formula);
    ast.pop();
  }

  setExpr = getFrontElement<NodeSetExpression>();
  if (setExpr == nullptr)
  {
    //if its not already a setexpression we try to make it one...
    //TODO: we need this potentially multiple times, either put in
    //a method or change the inheritance structure!
    auto newSetExpr = std::make_shared<NodeSetExpression>();
    newSetExpr->setRhs(getFrontElement<ASTNodeBase>());
    quantifiedFormula->setSetExpr(newSetExpr);
  }
  else
    quantifiedFormula->setSetExpr(setExpr);

  ast.pop();

  auto tuple = getFrontElement<NodeTuple>();

  //sanity check
  if (tuple == nullptr)
  {
    throw std::runtime_error("Expected tuple in quantified formula!");
  }

  ast.pop();
  quantifiedFormula->setTuple(tuple);

  ast.push(quantifiedFormula);
}

void ASTBuilder::addIn()
{
  auto inFormula = std::make_shared<NodeOperatorIn>();

  //we have something of the form <tuple> <setexpr>

  //TODO: find better type abstraction
  auto setExpr = getFrontElement<NodeSetExpression>();
  auto set = getFrontElement<NodeSet>();
  auto id = getFrontElement<NodeID>();

  if (setExpr == nullptr && set == nullptr && id == nullptr)
  {
    throw std::runtime_error("Expected setexpr, set or id in in-formula!");
  }

  inFormula->setSetExpr(getFrontElement<ASTNodeBase>());
  ast.pop();

  auto tuple = getFrontElement<NodeTuple>();

  //sanity check
  if (tuple == nullptr)
  {
    throw std::runtime_error("Expected tuple in in-formula!");
  }

  ast.pop();
  inFormula->setTuple(tuple);

  ast.push(inFormula);
}

void ASTBuilder::consumeVarNode()
{
  auto var = getFrontElement<NodeVariable>();
  if (var == nullptr)
  {
    throw std::runtime_error("Want to consume a variable when there is none!");
  }
  ast.pop();

  auto varList = getFrontElement<NodeVarList>();
  if (varList == nullptr)
  {
    throw std::runtime_error("Want to consume variable into something thats not a varlist!");
  }

  varList->addVariable(var);
}

void ASTBuilder::addForLoopAssign()
{
  auto forLoopAssign = std::make_shared<NodeForLoopAssignment>();

  //setexpr and tuple have already been created

  //TODO: should be created in everycase the <setexpr> rule gets executed!
  //if it's an id we need to create a setxpr,
  //otherwise it already has been created earlier...
  auto setExpr = getFrontElement<NodeSetExpression>();
  if (setExpr == nullptr)
  {
    auto setExprNew = std::make_shared<NodeSetExpression>();
    setExprNew->setRhs(getFrontElement<ASTNodeBase>()); //TODO: arbitrary, needs rethinking
    forLoopAssign->setSetExpr(setExprNew);
  }
  else
    forLoopAssign->setSetExpr(setExpr);

  ast.pop();

  auto tuple = getFrontElement<NodeTuple>();
  if (tuple == nullptr)
  {
    throw std::runtime_error("No tuple to build for-loop assign!");
  }

  ast.pop();
  forLoopAssign->setTuple(tuple);

  ast.push(forLoopAssign);
}

void ASTBuilder::addConditionalAssign()
{
  auto conditionalAssign = std::make_shared<NodeConditionalAssignment>();

  //formula has already been created...
  auto formula = getFrontElement<NodeFormulaBase>();
  if (formula == nullptr)
  {
    throw std::runtime_error("No formula to build conditional-assign!");
  }
  ast.pop();

  conditionalAssign->setFormula(formula);
  ast.push(conditionalAssign);
}

void ASTBuilder::addConditionalAssignElse()
{
  auto conditionalAssignment = getFrontElement<NodeConditionalAssignment>();

  if (conditionalAssignment == nullptr)
  {
    throw std::runtime_error(
        "Want to build else-claus for cond. ass., but there is no cond. ass.!");
  }

  conditionalAssignment->buildElseBlock(true);

}

void ASTBuilder::consumeAssignment()
{
  auto assignment = getFrontElement<NodeAssignmentBase>();
  ast.pop();

  if (assignment == nullptr)
  {
    throw std::runtime_error("Want to consume assignment when there is none!");
  }

  auto consumer = getFrontElement<ASTNodeBase>();

  //Different stuff can consume assignments...
  //TODO: need better abstraction, maybe baseclass should get addAssignment()
  auto actionEffect = std::dynamic_pointer_cast<NodeActionEffect>(consumer);
  auto activeSensing = std::dynamic_pointer_cast<NodeActiveSensing>(consumer);
  auto forLoopAssign = std::dynamic_pointer_cast<NodeForLoopAssignment>(consumer);
  auto conditionalAssign = std::dynamic_pointer_cast<NodeConditionalAssignment>(consumer);
  auto passiveSensing = std::dynamic_pointer_cast<NodePassiveSensingDecl>(consumer);

  //TODO: put this into baseclass
  if (actionEffect != nullptr)
  {
    actionEffect->addAssignment(assignment);
  }
  else if (activeSensing != nullptr)
  {
    activeSensing->addAssignment(assignment);
  }
  else if (forLoopAssign != nullptr)
  {
    forLoopAssign->addAssignment(assignment);
  }
  else if (conditionalAssign != nullptr)
  {
    conditionalAssign->addAssignment(assignment);
  }
  else if (passiveSensing != nullptr)
  {
    passiveSensing->addAssignment(assignment);
  }
  else
    throw std::runtime_error("Don't know what the consumer for the assignment is!");
}

void ASTBuilder::addEffect()
{
  auto effect = std::make_shared<NodeActionEffect>();
  ast.push(effect);
}

void ASTBuilder::addActiveSensing()
{
  auto activeSensing = std::make_shared<NodeActiveSensing>();

  //there must be a varlist for active sensing
  auto varList = getFrontElement<NodeVarList>();
  if (varList == nullptr)
  {
    throw std::runtime_error("There must be a varlist for active sensing, but there isn't!");
  }
  activeSensing->setVarList(varList);

  ast.pop();
  ast.push(activeSensing);
}

void ASTBuilder::addActionDeclNode(const std::string& actionName)
{
  auto actionDecl = std::make_shared<NodeActionDecl>();
  actionDecl->setActionName(std::make_shared<NodeID>(actionName));

  //TODO: find a better type abstraction, this is ugly!
  auto signalExpr = getFrontElement<NodeValueExpression>();
  auto signalInt = getFrontElement<NodeInteger>();
  auto signalString = getFrontElement<NodeString>();
  auto signalVar = getFrontElement<NodeVariable>();

  if (signalExpr != nullptr || signalInt != nullptr || signalString != nullptr
      || signalVar != nullptr)
  {
    actionDecl->setSignal(std::make_shared<NodeSignal>(getFrontElement<ASTNodeBase>()));
    ast.pop();
  }

  auto activeSensing = getFrontElement<NodeActiveSensing>();
  if (activeSensing != nullptr)
  {
    actionDecl->setActiveSensing(activeSensing);
    ast.pop();
  }

  auto actionEffect = getFrontElement<NodeActionEffect>();
  if (actionEffect != nullptr)
  {
    actionDecl->setActionEffect(actionEffect);
    ast.pop();
  }

  auto actionPrecondition = getFrontElement<NodeFormulaBase>();
  if (actionPrecondition != nullptr)
  {
    actionDecl->setActionPrecondition(std::make_shared<NodeActionPrecondition>(actionPrecondition));
    ast.pop();
  }

  auto paramList = getFrontElement<NodeVarList>();
  if (paramList != nullptr)
  {
    actionDecl->setVarList(paramList);
    ast.pop();
  }

  ast.push(actionDecl);
}

void ASTBuilder::addBlock()
{
  auto block = std::make_shared<NodeBlock>();
  ast.push(block);
}

void ASTBuilder::consumeStatement()
{
  auto stmt = getFrontElement<NodeStatementBase>();
  if (stmt == nullptr)
  {
    throw std::runtime_error("Want to consume a statement when there is none!");
  }
  ast.pop();

  //Only blocks can consume statements
  auto block = getFrontElement<NodeBlock>();
  if (block == nullptr)
  {
    throw std::runtime_error("There must be a block to consume a statement!");
  }

  block->addStatement(stmt);
}

void ASTBuilder::addProcDecl(const std::string& procName)
{
  auto procDecl = std::make_shared<NodeProcDecl>();
  procDecl->setProcName(std::make_shared<NodeID>(procName));

  //there must be a block...
  auto block = getFrontElement<NodeBlock>();
  if (block == nullptr)
  {
    throw std::runtime_error("There must be a block for a proc decl!");
  }
  procDecl->setBlock(block);

  ast.pop();

  //there can be a varlist for passive sensing
  auto varList = getFrontElement<NodeVarList>();
  if (varList != nullptr)
  {
    procDecl->setArgList(varList);
    ast.pop();
  }

  ast.push(procDecl);
}

void ASTBuilder::consumeValue()
{
  //get value
  auto val = getFrontElement<ASTNodeBase>();
  ast.pop();

  //get val_list
  auto valList = getFrontElement<NodeValueList>();
  if (valList == nullptr)
    throw std::runtime_error("No ValueList for consumeValue!");

  valList->addValue(val);
}

void ASTBuilder::addValueList()
{
  auto valList = std::make_shared<NodeValueList>();
  ast.push(valList);
}

void ASTBuilder::addActionExec(const std::string& actionToExecName)
{
  auto actionExec = std::make_shared<NodeActionExecution>();
  actionExec->setActionToExecName(std::make_shared<NodeID>(actionToExecName));

  auto execParams = getFrontElement<NodeValueList>();
  if (execParams != nullptr)
  {
    actionExec->setParameters(execParams);
    ast.pop();
  }

  ast.push(actionExec);
}

void ASTBuilder::addTest()
{
  auto test = std::make_shared<NodeTest>();

  auto formula = getFrontElement<NodeFormulaBase>();
  if (formula == nullptr)
  {
    throw std::runtime_error("There must be a formula to test!");
  }
  ast.pop();

  test->setFormula(formula);
  ast.push(test);
}

void ASTBuilder::addChoose()
{
  auto choose = std::make_shared<NodeChoose>();
  ast.push(choose);

}

void ASTBuilder::consumeBlock()
{
  auto block = getFrontElement<NodeBlock>();
  if (block == nullptr)
  {
    throw std::runtime_error("Want to consume block when there is none!");
  }
  ast.pop();

  //Get the consumer
  auto choose = getFrontElement<NodeChoose>();
  if (choose == nullptr)
  {
    throw std::runtime_error("Invalid type of the consumer of a block!");
  }

  choose->addBlock(block);
}

void ASTBuilder::addPick()
{
  auto pick = std::make_shared<NodePick>();

  auto block = getFrontElement<NodeBlock>();
  if (block == nullptr)
  {
    throw std::runtime_error("No block for pick!");
  }
  ast.pop();

  auto setexpr = getFrontElement<NodeSetExpression>();
  if (setexpr == nullptr)
  {
    //if its not already a setexpression we try to make it one...
    auto newSetExpr = std::make_shared<NodeSetExpression>();
    newSetExpr->setRhs(getFrontElement<ASTNodeBase>());
    pick->setSetExpr(newSetExpr);
  }
  else
  {
    pick->setSetExpr(setexpr);
  }
  ast.pop();

  auto tuple = getFrontElement<NodeTuple>();
  if (tuple == nullptr)
  {
    throw std::runtime_error("No tuple for pick!");
  }
  ast.pop();

  pick->setBlock(block);
  pick->setTuple(tuple);

  ast.push(pick);
}

void ASTBuilder::addForLoop()
{
  auto forLoop = std::make_shared<NodeForLoop>();

  auto block = getFrontElement<NodeBlock>();
  if (block == nullptr)
  {
    throw std::runtime_error("No block for for-loop!");
  }
  ast.pop();

  auto setexpr = getFrontElement<NodeSetExpression>();
  if (setexpr == nullptr)
  {
    //if its not already a setexpression we try to make it one...
    auto newSetExpr = std::make_shared<NodeSetExpression>();
    newSetExpr->setRhs(getFrontElement<ASTNodeBase>());
    forLoop->setSetExpr(newSetExpr);
  }
  else
  {
    forLoop->setSetExpr(setexpr);
  }

  ast.pop();

  auto tuple = getFrontElement<NodeTuple>();
  if (tuple == nullptr)
  {
    throw std::runtime_error("No tuple for for-loop!");
  }
  ast.pop();

  forLoop->setBlock(block);
  forLoop->setTuple(tuple);

  ast.push(forLoop);
}

void ASTBuilder::addConditional()
{
  auto conditional = std::make_shared<NodeConditional>();

  auto block1 = getFrontElement<NodeBlock>();
  if (block1 == nullptr)
  {
    throw std::runtime_error("No block for conditional!");
  }
  ast.pop();

  auto block2 = getFrontElement<NodeBlock>();
  if (block2 == nullptr) //if without else
  {
    conditional->setIfBlock(block1);
  }
  else //if + else
  {
    conditional->setIfBlock(block2);
    conditional->setElseBlock(block1);
    ast.pop();
  }

  auto formula = getFrontElement<NodeFormulaBase>();
  if (formula == nullptr)
  {
    throw std::runtime_error("No formula for conditional!");
  }
  ast.pop();

  conditional->setFormula(formula);

  ast.push(conditional);
}
void ASTBuilder::addWhileLoop()
{
  auto whileLoop = std::make_shared<NodeWhileLoop>();

  auto block = getFrontElement<NodeBlock>();
  if (block == nullptr)
  {
    throw std::runtime_error("No block for while-loop!");
  }
  ast.pop();

  auto formula = getFrontElement<NodeFormulaBase>();
  if (formula == nullptr)
  {
    throw std::runtime_error("No formula for while-loop!");
  }
  ast.pop();

  whileLoop->setFormula(formula);
  whileLoop->setBlock(block);

  ast.push(whileLoop);

}
void ASTBuilder::addSearch()
{
  auto search = std::make_shared<NodeSearch>();

  auto block = getFrontElement<NodeBlock>();
  if (block == nullptr)
  {
    throw std::runtime_error("No block for search!");
  }
  ast.pop();

  search->setBlock(block);

  ast.push(search);
}
