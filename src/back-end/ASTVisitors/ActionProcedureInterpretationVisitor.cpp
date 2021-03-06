/**
 * @file   ActionProcedureInterpretationVisitor.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Responsible for executing a YAGI program, i.e. traversing the AST via the implemented
 * visitor methods and executing the appropriate actions.
 */

/*
 This file is part of YAGI.

 YAGI is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3.0 of the License, or (at your option) any later version.

 YAGI is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with YAGI.
*/


#include "ActionProcedureInterpretationVisitor.h"

#include <algorithm>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>

#include "../../common/ASTNodeTypes/Domains/NodeDomainStringElements.h"
#include "../../utils/CommandLineArgsContainer.h"
#include "../Database/DatabaseConnectorBase.h"
#include "../ExecutableElementsContainer.h"
#include "../SQLGenerator.h"
#include "../Signals/IYAGISignalHandler.h"
#include "../Formulas/IFormulaEvaluator.h"
#include "../../utils/SetOperations.h"
#include "../TreeHelper.h"
#include "../../utils/RandomNumberGenerator.h"
#include "../../utils/ToStringHelper.h"
#include "../Database/DatabaseManager.h"
#include "../Database/DBHelper.h"
#include "../Formulas/FormulaEvaluator.h"
#include "../BackendFactory.h"
#include "../Variables/VariableTable.h"
#include "../Variables/VariableTableManager.h"
#include "../ExogenousEvents/ExoEventNotifier.h"

using yagi::database::DatabaseConnectorBase;
using yagi::execution::IYAGISignalHandler;
using yagi::formula::FormulaEvaluator;
using yagi::formula::IFormulaEvaluator;

namespace yagi {
namespace execution {

const std::string ActionProcedureInterpretationVisitor::DOMAIN_STRING_ID = "\"";
std::mutex coutMutex;

std::shared_ptr<std::vector<std::shared_ptr<BfsDataContainer>>>ActionProcedureInterpretationVisitor::bfsStatesQueue = std::make_shared<std::vector<std::shared_ptr<BfsDataContainer>>>();

ActionProcedureInterpretationVisitor::ActionProcedureInterpretationVisitor() :
    formulaEvaluator_(nullptr), db_(nullptr), signalReceiver_(nullptr), varTable_(nullptr), isSearch_(
    false), msgPrefix_("")
{
  this->exoEventConsumerName_ = name_;
  ExoEventNotifier::getInstance().registerEventConsumerIfNotRegistered(this);
}

ActionProcedureInterpretationVisitor::ActionProcedureInterpretationVisitor(
    std::shared_ptr<DatabaseConnectorBase> db) :
    formulaEvaluator_(nullptr), db_(db), signalReceiver_(nullptr), varTable_(nullptr), isSearch_(
    false), msgPrefix_("")
{
  this->exoEventConsumerName_ = name_;
  ExoEventNotifier::getInstance().registerEventConsumerIfNotRegistered(this);
}

ActionProcedureInterpretationVisitor::ActionProcedureInterpretationVisitor(
    std::shared_ptr<IFormulaEvaluator> formulaEvaluator, std::shared_ptr<DatabaseConnectorBase> db,
    std::shared_ptr<IYAGISignalHandler> signalReceiver, VariableTable& varTable, bool isSearch,
    const std::string& name) :
    formulaEvaluator_(formulaEvaluator), db_(db), signalReceiver_(signalReceiver), varTable_(
        &varTable), isSearch_(isSearch), msgPrefix_(""), name_(name)
{
  formulaEvaluator_->setContext(this);
  signalReceiver_->setIsSearch(isSearch);
  if (isSearch_)
  {
    msgPrefix_ = "[Search instance=" + name_ + "] ";
  }
  else
  {
    this->exoEventConsumerName_ = name_;
    ExoEventNotifier::getInstance().registerEventConsumerIfNotRegistered(this);
  }

}

ActionProcedureInterpretationVisitor::ActionProcedureInterpretationVisitor(VariableTable& varTable) :
    formulaEvaluator_(nullptr), db_(nullptr), signalReceiver_(nullptr), varTable_(&varTable), isSearch_(
    false), msgPrefix_("")
{
  this->exoEventConsumerName_ = name_;
  ExoEventNotifier::getInstance().registerEventConsumerIfNotRegistered(this);
}

ActionProcedureInterpretationVisitor::~ActionProcedureInterpretationVisitor()
{
  ExoEventNotifier::getInstance().unRegisterEventConsumer(this);
}

Any ActionProcedureInterpretationVisitor::visit(NodeID& id)
{
  return Any { id.getId() };
}

Any ActionProcedureInterpretationVisitor::visit(NodeActionPrecondition& ap)
{
  return Any { ap.getFormula()->accept(*this) };
}

Any ActionProcedureInterpretationVisitor::visit(NodeConstant& formulaConstant)
{
  return Any { formulaEvaluator_->evaluateConstant(&formulaConstant) };
}

Any ActionProcedureInterpretationVisitor::visit(NodeNegation& negation)
{
  return Any { formulaEvaluator_->evaluateNegation(&negation) };
}

Any ActionProcedureInterpretationVisitor::visit(NodeCompoundFormula& compoundFormula)
{
  return Any { formulaEvaluator_->evaluateCompoundFormula(&compoundFormula) };
}

Any ActionProcedureInterpretationVisitor::visit(NodeFormulaConnective& formulaConnective)
{
  return Any { formulaConnective.getFormulaConnective() };
}

Any ActionProcedureInterpretationVisitor::visit(NodeAtom& atom)
{
  return Any { formulaEvaluator_->evaluateAtom(&atom) };
}

Any ActionProcedureInterpretationVisitor::visit(NodeQuantifiedFormula& quantifiedFormula)
{
  return Any { formulaEvaluator_->evaluateQuantifiedFormula(&quantifiedFormula) };
}

Any ActionProcedureInterpretationVisitor::visit(NodeOperatorIn& inFormula)
{
  return Any { formulaEvaluator_->evaluateInFormula(&inFormula) };
}

Any ActionProcedureInterpretationVisitor::visit(NodeSignal& signal)
{
  if (!this->isSearch_ && this->name_ != "reproduceStateVisitor")
  {
    return triggerYagiSignal(signal, std::vector<std::string> { });
  }

  return Any { };
}

Any ActionProcedureInterpretationVisitor::triggerYagiSignal(NodeSignal& signal,
    std::vector<std::string> settingVariables)
{
  if (!signalReceiver_)
  {
    throw std::runtime_error("Want to send <signal> with no signal receiver set!");
  }

  auto signalData = signal.getSignalData()->accept(*this).get<std::string>();

  return Any { signalReceiver_->signal(signalData, settingVariables) };
}

Any ActionProcedureInterpretationVisitor::visit(NodeProcDecl& procDecl)
{
  auto procName = procDecl.getProcName()->accept(*this).get<std::string>();
  auto statements = procDecl.getBlock()->getStatements();

  for (const auto& stmt : statements)
  {
    auto ret = stmt->accept(*this);

    bool success = true;
    if (ret.hasType<bool>())
    {
      success = ret.get<bool>();
    }

    //'test' statement returns wether or not it holds
    if (auto isTest = std::dynamic_pointer_cast<NodeTest>(stmt))
    {
      std::string outText = "holds!";
      if (!success)
      {
        outText = "does NOT hold!";
      }

      if (CommandLineArgsContainer::getInstance().getShowDebugMessages() || !this->isSearch_)
      {
        std::lock_guard<std::mutex> lk(coutMutex);
        std::cout << ">>>> " << msgPrefix_ << "Test condition in procedure '" << procName << "' "
            << outText << std::endl;
      }
    }

    if (!success)
    {
      return Any { false };
    }
  }

  return Any { true };
}

Any ActionProcedureInterpretationVisitor::visit(NodeExogenousEventDecl& nodeExoEventDecl)
{
  auto exoEventName = nodeExoEventDecl.getExogenousEventName()->accept(*this).get<std::string>();
  auto exoEventAssignments = nodeExoEventDecl.getBlock();

  auto statements = exoEventAssignments->getStatements();
  for (const auto& stmt : statements)
  {
    stmt->accept(*this);
  }

  return Any { true };
}

Any ActionProcedureInterpretationVisitor::visit(NodeActionDecl& actionDecl)
{
  auto actionName = actionDecl.getActionName()->accept(*this).get<std::string>();

  if (auto ap = actionDecl.getActionPrecondition())
  {
    bool apHolds = ap->accept(*this).tryGetCopy<bool>(false);
    if (!apHolds)
    {
      if (CommandLineArgsContainer::getInstance().getShowDebugMessages()
          || (!this->isSearch_ && this->name_ != "reproduceStateVisitor"))
      {
        std::lock_guard<std::mutex> lk(coutMutex);
        std::cout << ">>>> " << msgPrefix_ << "AP for action '" + actionName + "' does NOT hold."
            << std::endl;
      }

      return Any { false };
    }

    if (CommandLineArgsContainer::getInstance().getShowDebugMessages()
        || (!this->isSearch_ && this->name_ != "reproduceStateVisitor"))
    {
      std::lock_guard<std::mutex> lk(coutMutex);
      std::cout << ">>>> " << msgPrefix_ << "AP for action '" + actionName + "' holds."
          << std::endl;
    }
  }

  if (auto signal = actionDecl.getSignal())
  {
    if (auto settingVarList = actionDecl.getSettingVarList())
    {
      auto varList = settingVarList->accept(*this).get<std::vector<std::string>>();
      auto settingVarAssignments = triggerYagiSignal(*signal.get(), varList).get<
          std::unordered_map<std::string, std::string>>();

      //add setting vars to vartable
      for (const auto& varAss : settingVarAssignments)
      {
        varTable_->addVariable(varAss.first, varAss.second);
      }
    }
    else
    {
      signal->accept(*this);
    }
  }

  if (auto actionEffect = actionDecl.getActionEffect())
  {
    auto statements = actionEffect->getBlock()->getStatements();
    for (const auto& stmt : statements)
    {
      stmt->accept(*this);
    }
  }

  return Any { true };
}

Any ActionProcedureInterpretationVisitor::visit(NodeValueList& valueList)
{
  std::vector<std::string> vals;
  auto valueNodes = valueList.getValues();

  for (const auto& valueNode : valueNodes)
  {
    vals.push_back(treeHelper::getValueFromValueNode(valueNode.get(), *this, varTable_));
  }

  return Any { vals };
}

Any ActionProcedureInterpretationVisitor::visit(NodeVarList& varList)
{
  std::vector<std::string> variables { };
  auto varNodes = varList.getVariables();

  std::for_each(std::begin(varNodes), std::end(varNodes),
      [this,&variables](const std::shared_ptr<NodeVariable>& varNode)
      {
        variables.push_back(varNode->accept(*this).get<std::string>());
      });

  return Any { variables };
}

Any ActionProcedureInterpretationVisitor::visit(NodeBlock& block)
{
  bool success = true;

  for (const auto& stmt : block.getStatements())
  {
    auto ret = stmt->accept(*this);
    if (ret.hasType<bool>())
    {
      bool rc = ret.get<bool>();
      if (!rc)
      {
        success = false;
        break;
      }
    }
  }

  return Any { success };
}

Any ActionProcedureInterpretationVisitor::visit(NodeSearch& search)
{
//Fire up a temporary db, temporary varTable and search for sequence of actions
  auto tempDB = DatabaseManager::getInstance().getCloneWithNewName(
      DatabaseManager::getInstance().MAIN_DB_NAME, "tempDB_" + std::to_string(getNowTicks()));

  std::string tempVarTableName = "tempVarTable_" + std::to_string(getNowTicks());
  auto& tempVarTable = VariableTableManager::getInstance().getCloneWithNewName(
      VariableTableManager::getInstance().MAIN_VAR_TABLE_ID, tempVarTableName);

  auto formulaEvaluator = std::make_shared<FormulaEvaluator>(&tempVarTable, tempDB.get());

  ActionProcedureInterpretationVisitor v(formulaEvaluator, tempDB,
      BackendFactory::getInstance().getBackend()->getSignalHandler(), tempVarTable, true,
      "<searchMain>");

  bool searchResult = false;

  std::atomic_bool finished;
  finished = false;

  std::cout << "Searching for solution..." << std::endl;

  std::thread t([&]()
  {
    searchResult = search.getBlock()->accept(v).get<bool>();
    finished = true;
  });

  while (!finished)
  {
    std::chrono::milliseconds dura(50);
    std::this_thread::sleep_for(dura);
  }

  t.join();

  if (searchResult)
  {

    std::cout << ">>>> Search found valid path! Executing..." << std::endl;
    this->choices_ = v.choices_;

    while (choices_.size())
    {
      choicesForOnlineExecution.push_back(choices_.at(0));
      choices_.erase(std::begin(choices_));
    }

    //since SignalHandlerFactory might still think we are in 'search mode'
    //we need to tell it otherwise...
    //Since we can collapse cascaded search blocks without changing the semantics
    //(still needs to be done!) from this point on we are guaranteed to be not in 'search mode' anymore
    this->signalReceiver_->setIsSearch(false);

    for (const auto& stmt : search.getBlock()->getStatements())
    {
      stmt->accept(*this);
    }
  }
  else
  {
    std::cout << ">>>> search could NOT find valid path!" << std::endl;
  }

//Cleanup
  DatabaseManager::getInstance().deleteDB(tempDB->getDbName());
  VariableTableManager::getInstance().deleteVariableTable(tempVarTableName);

  return Any { };
}

Any ActionProcedureInterpretationVisitor::visit(NodeProcExecution& procExec)
{
  if (!formulaEvaluator_)
    throw std::runtime_error("No FormulaEvaluator passed to InterpretationVisitor!");

  if (!db_)
    throw std::runtime_error("No Database passed to InterpretationVisitor!");

  auto actionOrProcName = procExec.getProcToExecName()->accept(*this).get<std::string>();
  bool procExecRetVal = true;

  std::vector<std::string> argList { };
  if (auto paramNode = procExec.getParameters())
  {
    argList = paramNode->accept(*this).get<std::vector<std::string>>();
  }

  varTable_->addScope();

  std::vector<std::string> paramList { };
  if (auto actionToExecute = ExecutableElementsContainer::getInstance().getAction(actionOrProcName,
      argList.size()))
  {
    //Wait here for execution signal
    if (isSearch_ && name_ != "<searchMain>")
    {
      while (!doStep_ && !cancelled_)
      {
        std::chrono::milliseconds dura(50);
        std::this_thread::sleep_for(dura);
      }

      doStep_ = false;
    }

    if (!isSearch_)
    {
      applyExoEventData();
    }

    if (auto paramNodeList = actionToExecute->getVarList())
    {
      paramList = paramNodeList->accept(*this).get<std::vector<std::string>>();
    }

    //set param values for action call
    for (size_t i = 0; i != paramList.size(); i++)
    {
      varTable_->addVariable(paramList[i], argList[i]);
    }

    auto ret = actionToExecute->accept(*this);
    if (ret.hasType<bool>())
    {
      procExecRetVal = ret.get<bool>();
    }
    else
    {
      procExecRetVal = true;
    }

    if (isSearch_ && name_ != "<searchMain>")
    {
      //After execution, signal that we're done
      stepDone_ = true;
    }
  }
  else if (auto procToExecute = ExecutableElementsContainer::getInstance().getProcedure(
      actionOrProcName, argList.size()))
  {
    if (auto paramNodeList = procToExecute->getArgList())
    {
      paramList = paramNodeList->accept(*this).get<std::vector<std::string>>();
    }

    //set param values for action call
    for (size_t i = 0; i != paramList.size(); i++)
    {
      varTable_->addVariable(paramList[i], argList[i]);
    }

    auto ret = procToExecute->accept(*this);
    if (ret.hasType<bool>())
    {
      procExecRetVal = ret.get<bool>();
    }
    else
    {
      procExecRetVal = true;
    }
  }
  else if (ExecutableElementsContainer::getInstance().actionNameExists(actionOrProcName))
  {
    if (CommandLineArgsContainer::getInstance().getShowDebugMessages()
        || (!this->isSearch_ && this->name_ != "reproduceStateVisitor"))
    {
      std::cout << ">>>> " << msgPrefix_ << " action " << actionOrProcName
          << " is used wrong possibilies are : " << std::endl;
      for (const auto& action_decl : ExecutableElementsContainer::getInstance().actionDeclerations(
          actionOrProcName))
        std::cout << ">>>> " << msgPrefix_ << " " << action_decl.name_ << " with arrity "
            << action_decl.arity_ << std::endl;
      std::cout << ">>>> " << msgPrefix_ << "[WARNING] will not execute the action " << "..."
          << std::endl;
    }
  }
  else if (ExecutableElementsContainer::getInstance().procNameExists(actionOrProcName))
  {
    if (CommandLineArgsContainer::getInstance().getShowDebugMessages()
        || (!this->isSearch_ && this->name_ != "reproduceStateVisitor"))
    {
      std::cout << ">>>> " << msgPrefix_ << " procedure " << actionOrProcName
          << " is used wrong possibilies are : " << std::endl;
      for (const auto& proc_decl : ExecutableElementsContainer::getInstance().procDeclerations(
          actionOrProcName))
        std::cout << ">>>> " << msgPrefix_ << " " << proc_decl.name_ << " with arrity "
            << proc_decl.arity_ << std::endl;
      std::cout << ">>>> " << msgPrefix_ << "[WARNING] will not execute the procedure " << "..."
          << std::endl;
    }
  }

  varTable_->removeScope();

  return Any { procExecRetVal };
}

Any ActionProcedureInterpretationVisitor::visit(NodeAssignmentOperator& assOp)
{
  return Any { assOp.getOperator() };
}

Any ActionProcedureInterpretationVisitor::visit(NodeIDAssignment& idAssign)
{
  std::vector<std::shared_ptr<ASTNodeBase<>>>newNodes;

  auto lhsFluentName = idAssign.getFluentName()->accept(*this).get<std::string>();

//the rhs is a (shadow-)fluent/fact for sure, so we get the name here
  auto rhsFluentName = idAssign.getSetExpr()->accept(*this).get<std::string>();
  auto assignOp = idAssign.getOperator()->accept(*this).get<AssignmentOperator>();

//Depending on the assignment operator we need to build different node sequences
  switch (assignOp)
  {
    case AssignmentOperator::AddAssign:
    newNodes.push_back(
        std::static_pointer_cast<ASTNodeBase<>>(
            buildAssignmentRewritingLoop(lhsFluentName, SitCalcActionType::AddAssign,
                rhsFluentName)));
    break;

    case AssignmentOperator::RemoveAssign:
    newNodes.push_back(
        std::static_pointer_cast<ASTNodeBase<>>(
            buildAssignmentRewritingLoop(lhsFluentName, SitCalcActionType::RemoveAssign,
                rhsFluentName)));
    break;

    //F = F' is specified as F -= F; followed by F += F'
    case AssignmentOperator::Assign:
    newNodes.push_back(
        std::static_pointer_cast<ASTNodeBase<>>(
            buildAssignmentRewritingLoop(lhsFluentName, SitCalcActionType::RemoveAssign,
                lhsFluentName)));
    newNodes.push_back(
        std::static_pointer_cast<ASTNodeBase<>>(
            buildAssignmentRewritingLoop(lhsFluentName, SitCalcActionType::AddAssign,
                rhsFluentName)));
    break;

    default:
    throw std::runtime_error("Unknown assignment operator!");
  }

  for (const auto& node : newNodes)
  {
    node->accept(*this);
  }

  return Any
  {};
}

std::shared_ptr<NodeForLoop> ActionProcedureInterpretationVisitor::buildAssignmentRewritingLoop(
    std::string lhsFluentName, SitCalcActionType actionType, std::string rhsFluentName)
{
  //Build foreach AST for fluent  assignment
  auto loop = std::make_shared<NodeForLoop>();

  //ActionProcedureInterpretationVisitor apiv(DatabaseManager::getInstance().getMainDB());
  auto newSetExpr = std::make_shared<NodeSetExpression>();
  newSetExpr->setLhs(std::make_shared<NodeID>(rhsFluentName));
  loop->setSetExpr(newSetExpr);

  //Deduce variable tuple for for-loop from (shadow) fluent
  auto tupleCount = db_->executeQuery(
      SQLGenerator::getInstance().getSqlStringNumberOfColumnsInTable(rhsFluentName)).size();

  auto tuple = std::make_shared<NodeTuple>();
  auto sitcalcActionExec = std::make_shared<NodeSitCalcActionExecution>();
  auto functionArgList = std::make_shared<NodeValueList>();

  for (size_t i = 0; i < tupleCount; i++)
  {
    auto var = std::make_shared<NodeVariable>(
        "$_x" + std::to_string(i) + "_" + std::to_string(getNowTicks()));
    tuple->addTupleValue(var);
    functionArgList->addValue(var);
  }
  loop->setTuple(tuple);

  sitcalcActionExec->setActionType(actionType);
  sitcalcActionExec->setParameters(functionArgList);
  sitcalcActionExec->setFluentName(std::make_shared<NodeID>(lhsFluentName));

  auto block = std::make_shared<NodeBlock>();
  block->addStatement(sitcalcActionExec);
  loop->setBlock(block);

  return loop;
}

Any ActionProcedureInterpretationVisitor::visit(NodeFluentDecl& fluentDecl)
{
  auto tableName = fluentDecl.getFluentName()->accept(*this).get<std::string>();
  std::vector<std::vector<std::string>> domains;

  for (const auto& domainNode : fluentDecl.getDomains())
  {
    domains.push_back(domainNode->accept(*this).get<std::vector<std::string>>());
  }

  auto sqlStrings = SQLGenerator::getInstance().getSqlStringsCreateTableAndDomains(tableName,
      domains);

  for (const auto& sqlString : sqlStrings)
  {
    db_->executeNonQuery(sqlString);
  }

  return Any { };
}

Any ActionProcedureInterpretationVisitor::visit(NodeDomainString& nodeDomainString)
{
  return Any { std::vector<std::string> { DOMAIN_STRING_ID } };
}

Any ActionProcedureInterpretationVisitor::visit(NodeDomainStringElements& nodeDomainStringElements)
{
  std::vector<std::string> domainElements;
  for (const auto& stringNode : nodeDomainStringElements.getDomainElements())
  {
    domainElements.push_back(stringNode->accept(*this).get<std::string>());
  }

  return Any { domainElements };
}

Any ActionProcedureInterpretationVisitor::visit(NodeSet& set)
{
  //Build shadow fluent for set
  std::vector<std::vector<std::string>> valueSet;
  std::vector<std::vector<std::string>> domains;

  auto tuples = set.getTuples();

  //build strings to add to the DB and deduce domains
  bool first = true;
  for (const auto& nodeTuple : tuples)
  {
    auto tupleElements = nodeTuple->accept(*this).get<std::vector<std::string>>();

    std::vector<std::string> vals;
    for (const auto& tupleVal : tupleElements)
    {
      if (tupleVal[0] == '$') //it's a variable
      {
        vals.push_back(varTable_->getVariableValue(tupleVal));
      }
      else //it's a string value
      {
        vals.push_back(tupleVal);
      }
    }
    valueSet.push_back(vals);

    int idx = 0;

    //add values to respective domains
    for (const auto& str : vals)
    {
      if (!first)
      {
        domains[idx].push_back(str);
      }
      else
      {
        domains.push_back( { str });
      }

      idx++;
    }

    first = false;
  }

  //save shadow fluent to db
  auto shadowFluentName = "shadow" + std::to_string(getNowTicks());

  NodeFluentDecl shadowFluentNode;
  shadowFluentNode.setFluentName(std::make_shared<NodeID>(shadowFluentName));

  for (const auto& domain : domains)
  {
    auto domainNode = std::make_shared<NodeDomainStringElements>();
    for (const auto& str : domain)
    {
      domainNode->addStringToDomain(std::make_shared<NodeString>(str));
    }
    shadowFluentNode.addDomain(domainNode);
  }

  visit(shadowFluentNode);

  //assign
  auto sqlStrings = SQLGenerator::getInstance().getSqlStringsForIDAssign(shadowFluentName, valueSet,
      AssignmentOperator::Assign);

  for (const auto& stmt : sqlStrings)
  {
    db_->executeNonQuery(stmt);
  }

  //add the info the that fluent is a shadow fluent
//  if (!db_->executeQuery(
//      SQLGenerator::getInstance().getSqlStringExistsTable(
//          SQLGenerator::getInstance().SHADOW_FLUENTS_TABLE_NAME_)).size())
//  {
//    db_->executeNonQuery(SQLGenerator::getInstance().getSqlStringCreateShadowFluentsTable());
//  }

  db_->executeNonQuery(
      SQLGenerator::getInstance().getSqlStringMakeTableShadowFluent(shadowFluentName));

  return Any { shadowFluentName };
}

Any ActionProcedureInterpretationVisitor::visit(NodeTuple& tuple)
{
  //Build vector with tuple values
  std::vector<std::string> tupleVals;

  auto values = tuple.getTupleValues();

  for (const auto& value : values)
  {
    auto val = value->accept(*this).get<std::string>();
    tupleVals.push_back(val);
  }

  return Any { tupleVals };
}

Any ActionProcedureInterpretationVisitor::visit(NodeVariable& variable)
{
  return Any { variable.getVarName() };
}

Any ActionProcedureInterpretationVisitor::visit(NodeString& str)
{
  auto ret = str.getString();

  //strip trailing and leading " if neccessary
  if (ret[0] == '"' && ret[ret.size() - 1] == '"')
  {
    return Any { ret.substr(1, ret.size() - 2) };
  }
  else
  {
    return Any { ret };
  }
}

Any ActionProcedureInterpretationVisitor::visit(NodeAtomConnective& atomConnective)
{
  return Any { atomConnective.getAtomConnective() };
}

Any ActionProcedureInterpretationVisitor::visit(NodeValueExpression& valExpr)
{
  std::string lhsResult = "", rhsResult = "";
  ExprOperator exprOp = ExprOperator::Unknown;

  if (auto lhs = valExpr.getLhs())
  {
    if (auto recursiveValExpr = std::dynamic_pointer_cast<NodeValueExpression>(lhs))
    {
      lhsResult = recursiveValExpr->accept(*this).get<std::string>();
    }
    else
      lhsResult = yagi::treeHelper::getValueFromValueNode(lhs.get(), *this, varTable_);
  }

  if (auto rhs = valExpr.getRhs())
  {
    if (auto recursiveValExpr = std::dynamic_pointer_cast<NodeValueExpression>(rhs))
    {
      lhsResult = recursiveValExpr->accept(*this).get<std::string>();
    }
    else
      rhsResult = yagi::treeHelper::getValueFromValueNode(rhs.get(), *this, varTable_);
  }

  if (auto op = valExpr.getOperator())
  {
    exprOp = op->getOperator();
  }
  else
  {
//    auto nodeString = std::make_shared<NodeString>(lhsResult);
//    return Any { nodeString };
    return Any { lhsResult };
  }

  if (exprOp == ExprOperator::Plus)
  {
    return Any { lhsResult + rhsResult };
//    auto nodeString = std::make_shared<NodeString>(lhsResult + rhsResult);
//    return Any { nodeString };
  }
  else
    throw std::runtime_error("Unknown <setexpr> operator!");

}

Any ActionProcedureInterpretationVisitor::visit(NodeSetExpression& setExpr)
{
  std::vector<std::vector<std::string>> lhsResultVector, rhsResultVector;
  ExprOperator exprOp = ExprOperator::Unknown;

  auto lhs = setExpr.getLhs();
  auto lhsResult = lhs->accept(*this);

//get data from (shadow-) fluent
  lhsResultVector = db_->executeQuery(
      SQLGenerator::getInstance().getSqlStringSelectAll(lhsResult.get<std::string>()));

  if (auto op = setExpr.getOperator())
  {
    exprOp = op->getOperator();
  }
  else //it's just a set and no full <setexpr>, so we return the (shadow-) fluent name
  {
    return Any { lhsResult.get<std::string>() };
  }

  auto rhs = setExpr.getRhs();
  auto rhsResult = rhs->accept(*this);

//get data from (shadow-) fluent
  rhsResultVector = db_->executeQuery(
      SQLGenerator::getInstance().getSqlStringSelectAll(rhsResult.get<std::string>()));

  std::vector<std::vector<std::string>> result;
  if (exprOp == ExprOperator::Plus)
  {
    result = yagi::operations::buildUnion(lhsResultVector, rhsResultVector);
  }
  else if (exprOp == ExprOperator::Minus)
  {
    result = yagi::operations::buildComplement(lhsResultVector, rhsResultVector);
  }
  else
    throw std::runtime_error("Unknown <setexpr> operator!");

//Cleanup fluents for lhs and rhs if they are shadow fluents
  if (isShadowFluent(lhsResult.get<std::string>(), *db_.get()))
  {
    cleanupShadowFluent(lhsResult.get<std::string>(), *db_.get());
  }
  if (isShadowFluent(rhsResult.get<std::string>(), *db_.get()))
  {
    cleanupShadowFluent(rhsResult.get<std::string>(), *db_.get());
  }

//Build new <set> and shadow fluent
  NodeSet nodeResult;

  std::for_each(std::begin(result), std::end(result),
      [this, &nodeResult](const std::vector<std::string>& tupleString)
      {
        auto tupleNode = std::make_shared<NodeTuple>();

        std::for_each(std::begin(tupleString), std::end(tupleString),
            [&tupleNode](const std::string& str)
            {
              tupleNode->addTupleValue(std::make_shared<NodeString>(str));
            });

        nodeResult.addTuple(tupleNode);
      });

  auto newShadowFluentName = visit(nodeResult).get<std::string>();
  return Any { newShadowFluentName };
}

Any ActionProcedureInterpretationVisitor::visit(NodeVariableAssignment & varAss)
{
  auto val = yagi::treeHelper::getValueFromValueNode(varAss.getValue().get(), *this, varTable_);
  auto varName = varAss.getVariable()->accept(*this).get<std::string>();

  varTable_->addVariable(varName, val);

  return Any { };
}

Any ActionProcedureInterpretationVisitor::visit(NodeWhileLoop& whileLoop)
{
  auto statements = whileLoop.getBlock()->getStatements();
  bool solutionFound = false;

  auto initialState = std::make_shared<BfsDataContainer>();
  initialState->setState(this->db_);
  bfsStatesQueue->push_back(initialState);

  bool first = true;

  if (this->isSearch_)
  {
    while (!solutionFound)
    {
      while (bfsStatesQueue->size())
      {
        if (!first)
        {
          std::string reproduceStateVarTableName = "reproduceStateVarTable"
              + std::to_string(getNowTicks());
          auto reproduceStateDB = DatabaseManager::getInstance().getCloneWithNewName(
                  db_->getDbName(),
              "reproduceStateDB_" + std::to_string(getNowTicks()));

          auto& reproduceStateVarTable = VariableTableManager::getInstance().getCloneWithNewName(
                  varTable_->getName(), reproduceStateVarTableName);

          auto reproduceStateFormulaEvaluator = std::make_shared<FormulaEvaluator>(
              &reproduceStateVarTable, reproduceStateDB.get());

          ActionProcedureInterpretationVisitor reproduceStateVisitor(reproduceStateFormulaEvaluator,
              reproduceStateDB, BackendFactory::getInstance().getBackend()->getSignalHandler(),
              reproduceStateVarTable, false, "reproduceStateVisitor");

          reproduceStateVisitor.choicesForOnlineExecution = bfsStatesQueue->at(0)->getChoices();

          bool doBreak = false;
          while (whileLoop.getFormula()->accept(reproduceStateVisitor).get<bool>() && !doBreak)
          {
            for (const auto& stmt : statements)
            {
              auto ret = stmt->accept(reproduceStateVisitor);
              if (!ret.get<bool>())
              {
                doBreak = true;
                break;
              }
            }
          }

          bfsStatesQueue->at(0)->setState(reproduceStateVisitor.db_);
        }

        std::cout << "[Search] Number of states to search: " << bfsStatesQueue->size() << std::endl;

        std::string tempVarTableName = "tempVarTable_" + std::to_string(getNowTicks());
        auto& tempVarTable = VariableTableManager::getInstance().getCloneWithNewName(
                varTable_->getName(), tempVarTableName);

        auto formulaEvaluator = std::make_shared<FormulaEvaluator>(&tempVarTable,
            bfsStatesQueue->at(0)->getState().get());

//        std::cout << "use name for search " << name_ << std::endl;
        std::string name_to_use = name_;
        if(bfsStatesQueue->size() > 1)
        	name_to_use  = "test";

//        std::cout << "name used for inner execution for search " << name_to_use << std::endl;

        ActionProcedureInterpretationVisitor v(formulaEvaluator, bfsStatesQueue->at(0)->getState(),
            BackendFactory::getInstance().getBackend()->getSignalHandler(), tempVarTable, true,
			name_to_use);

        v.choices_ = bfsStatesQueue->at(0)->getChoices();

        if (!whileLoop.getFormula()->accept(v).get<bool>())
        {
          solutionFound = true;
          this->choices_ = v.choices_;
          break;
        }

        for (const auto& stmt : statements)
        {
          stmt->accept(v);
        }

        bfsStatesQueue->erase(std::begin(*bfsStatesQueue));

        first = false;
      }

      if (solutionFound)
      {
        std::cout << "FOUND SOLUTION!" << std::endl;
      }
    }
    return Any { };
  }
  else
  {
    while (whileLoop.getFormula()->accept(*this).get<bool>())
    {
      for (const auto& stmt : statements)
      {
        auto ret = stmt->accept(*this);

        if (ret.hasType<bool>() && ret.get<bool>() == false) //YagiTrans does not hold
        {
          return Any { false };
        }

        if (isSearch_ && cancelled_ && name_ != "<searchMain>")
        {
          return Any { };
        }
      }
    }
    return Any { true };
  }
}

Any ActionProcedureInterpretationVisitor::visit(NodeTest& test)
{
  //return test condition result to handle it in proc execution
  bool testHolds = test.getFormula()->accept(*this).get<bool>();

  std::string outText = "holds!";
  if (!testHolds)
  {
    outText = "does NOT hold!";
  }

  if (CommandLineArgsContainer::getInstance().getShowDebugMessages() || !this->isSearch_)
  {
    std::lock_guard<std::mutex> lk(coutMutex);
    std::cout << ">>>> " << msgPrefix_ << "Test condition " << outText << std::endl;
  }

  // std::cout << "test will return any" << std::endl;
  return Any { testHolds };
}

Any ActionProcedureInterpretationVisitor::visit(NodeForLoop& forLoop)
{
  auto varTuple = forLoop.getTuple()->accept(*this).get<std::vector<std::string>>();
  auto setResult = forLoop.getSetExpr()->accept(*this);
  auto statements = forLoop.getBlock()->getStatements();

//get data from shadow fluent set
  auto set = db_->executeQuery(
      SQLGenerator::getInstance().getSqlStringSelectAll(setResult.get<std::string>()));

//add vars to vartable
  varTable_->addScope();

  for (const auto& varName : varTuple)
  {
    if (varName[0] == '$')
    {
      if (!varTable_->variableExists(varName))
      {
        varTable_->addVariable(varName);
      }
    }
  }

//set values to variables and execute <block>
  for (const auto& tuple : set)
  {
    size_t tupleValIdx = 0;
    int varIndex = 0;
    while (tupleValIdx < tuple.size())
    {
      if (varTuple[varIndex][0] == '$' && varTable_->isVariableInCurrentScope(varTuple[varIndex]))
      {
        varTable_->setVariable(varTuple[varIndex], tuple[tupleValIdx]);
        tupleValIdx++;
      }
      varIndex++;
    }

    for (const auto& stmt : statements)
    {
      stmt->accept(*this);
    }
  }

  varTable_->removeScope();

//Cleanup shadow fluent in case it is one
  if (isShadowFluent(setResult.get<std::string>(), *db_.get()))
  {
    cleanupShadowFluent(setResult.get<std::string>(), *db_.get());
  }

  return Any { };
}

Any ActionProcedureInterpretationVisitor::visit(NodeSitCalcActionExecution& sitCalcAction)
{
  if (!db_)
    throw std::runtime_error("No Database passed to InterpretationVisitor!");

  auto actionType = sitCalcAction.getActionType();
  auto fluentName = sitCalcAction.getFluentName()->accept(*this).get<std::string>();

  std::vector<std::string> argList { };
  if (auto paramNode = sitCalcAction.getParameters())
  {
    argList = paramNode->accept(*this).get<std::vector<std::string>>();
  }

  if (actionType == SitCalcActionType::Unknown)
  {
    throw std::runtime_error("Unknown sit calc action!");
  }

  //Enforce action precondition of add/remove, i.e. the elements
  //must be part of the sort of the corresponding domain
  for (size_t argIdx = 0; argIdx < argList.size(); argIdx++)
  {
    if (!db_->executeQuery(
        SQLGenerator::getInstance().getSqlStringExistsDomainTable(fluentName, argIdx + 1)).size())
    {
      std::string errorMsg { "SitCalc action: '" };

      errorMsg += (
          actionType == SitCalcActionType::AddAssign ? std::string("add") : std::string("remove"))
          + "' ";
      errorMsg += "Fluent Name: '" + fluentName + "' ";
      errorMsg += "Parameters: " + tupleToString(argList);

      std::cout
          << "SitCalc action precondition does not hold! Arity mismatch! Unable to continue, possibly invalid situation!\n"
          << errorMsg << std::endl;
      std::terminate();
    }

    auto sortVals = db_->executeQuery(
        SQLGenerator::getInstance().getSqlStringGetDomainElements(fluentName, argIdx + 1));
    if (std::find(std::begin(sortVals[0]), std::end(sortVals[0]), argList[argIdx])
        == std::end(sortVals[0]))
    {
      std::string errorMsg { "SitCalc action: '" };

      errorMsg += (
          actionType == SitCalcActionType::AddAssign ? std::string("add") : std::string("remove"))
          + "' ";
      errorMsg += "Fluent Name: '" + fluentName + "' ";
      errorMsg += "Parameters: " + tupleToString(argList);

      std::cout << "SitCalc action precondition does not hold! Argument: '" << argList[argIdx]
          << "' at position " << argIdx
          << " is not specified within the domain! Unable to continue, possibly invalid situation!\n"
          << errorMsg << std::endl;
      std::terminate();
    }
  }

//YAGI uses *only* addF and removeF as sitcalc actions per fluent F.
//These actions are specified to make a fluent true (or false) for a specific
//parameter vector, i.e. a YAGI tuple.
//Making "true"/"false" corresponds to a DB insert/delete in this implementation
  auto sqlString = SQLGenerator::getInstance().getSqlStringForTupleAssign(fluentName, argList,
      actionType);

  db_->executeNonQuery(sqlString);

  return Any { };

}

Any ActionProcedureInterpretationVisitor::visit(NodeConditional& conditional)
{
  auto conditionalTruthVal = conditional.getFormula()->accept(*this).get<bool>();

  std::vector<std::shared_ptr<NodeStatementBase>> statements;
  if (conditionalTruthVal)
  {
    statements = conditional.getIfBlock()->getStatements();
  }
  else
  {
    if (auto elseBlock = conditional.getElseBlock())
    {
      statements = elseBlock->getStatements();
    }
  }

  bool success = true;

//if the if-condition doesn't hold and there is no else-block we're done
  if (!statements.size())
  {
    return Any { true };
  }

  for (const auto& stmt : statements)
  {
    auto ret = stmt->accept(*this);

    if (ret.hasType<bool>())
    {
      success = success && ret.get<bool>();

      if (!success)
      {
        break;
      }
    }
  }

  return Any { success };
}

Any ActionProcedureInterpretationVisitor::visit(NodeChoose& choose)
{
  auto blocks = choose.getBlocks();

  if (!isSearch_)
  {
    int idx = -1;
    if (choicesForOnlineExecution.empty())
    {
      //XXX: HACKHACK if we reproduce state in BFS we execute all choices known
      //and stop if we ran out of choices, i.e. choicesForOnlineExecution is empty!
      if (this->name_ == "reproduceStateVisitor")
      {
        return Any { false };
      }

      RandomNumberGenerator rng;
      idx = rng.getRandomNumber(0, blocks.size() - 1);
    }
    else
    {
      idx = choicesForOnlineExecution.at(0);
      choicesForOnlineExecution.erase(std::begin(choicesForOnlineExecution));
    }

    if (CommandLineArgsContainer::getInstance().getShowDebugMessages()
        || (!this->isSearch_ && this->name_ != "reproduceStateVisitor"))
    {
      std::cout << ">>>> " << msgPrefix_ << "Choosing block " << std::to_string(idx + 1) << "..."
          << std::endl;
    }

    auto stmts = blocks.at(idx)->getStatements();

    bool success = true;
    for (const auto& stmt : stmts)
    {
      auto ret = stmt->accept(*this);

      if (ret.hasType<bool>())
      {
        success = success && ret.get<bool>();
        if (!success)
        {
          break;
        }
      }
    }

    return Any { success };
  }
  else
  {
    std::vector<std::tuple<std::shared_ptr<ActionProcedureInterpretationVisitor>, std::thread>> threads;
    std::vector<int> results;
    std::mutex chooseSearchResultMutex;
    std::mutex chooseVisitorMutex;
    std::shared_ptr<ActionProcedureInterpretationVisitor> v = nullptr;

    for (size_t idx = 0; idx < blocks.size(); idx++)
    {
      //Fire up a temporary db, temporary varTable and search for sequence of actions
      std::string name = "<search " + std::to_string(idx + 1) + ", choosing block "
          + std::to_string(idx + 1) + ">";

      auto tempDB = DatabaseManager::getInstance().getCloneWithNewName(db_->getDbName(),
          name + "DB_" + std::to_string(getNowTicks()));

      std::string tempVarTableName = name + "VarTable_" + std::to_string(getNowTicks());
      auto& tempVarTable = VariableTableManager::getInstance().getCloneWithNewName(
          varTable_->getName(), tempVarTableName);

      auto formulaEvaluator = std::make_shared<FormulaEvaluator>(&tempVarTable, tempDB.get());

      {
        std::lock_guard<std::mutex> lk(chooseVisitorMutex);
        v = std::make_shared<ActionProcedureInterpretationVisitor>(formulaEvaluator, tempDB,
            BackendFactory::getInstance().getBackend()->getSignalHandler(), tempVarTable, true,
            name);
      }

      v->choices_ = this->choices_;
      v->choices_.push_back(idx);
      this->children_.push_back(v);

      {
        std::lock_guard<std::mutex> lk(chooseSearchResultMutex);
        results.push_back(-1);
      }

      std::thread t([&blocks,idx,v,&results,&chooseVisitorMutex,&chooseSearchResultMutex]()
      {
        while (!v->run)
        {
          std::chrono::milliseconds dura(20);
          std::this_thread::sleep_for(dura);
        }

        ActionProcedureInterpretationVisitor* ctx = nullptr;

        {
          std::lock_guard<std::mutex> lk(chooseVisitorMutex);
          ctx = v.get();
        }
        auto stmts = blocks.at(idx)->getStatements();

        bool rc = true;
        for (const auto& stmt : stmts)
        {
          auto ret = stmt->accept(*ctx);

          if (ret.hasType<bool>())
          {
            rc = rc && ret.get<bool>();
          }
        }

        {
          std::lock_guard<std::mutex> lk(chooseSearchResultMutex);
          results[idx] = rc ? 1 : 0;
        }

        v->stepDone_ = true;
      });
      threads.push_back(std::make_tuple(v, std::move(t)));
    }

    size_t successIndex = 0;
    bool found = false;
    bool allDoneNoResult = true;

    do
    {

      for (auto& thread : threads)
      {
        std::get<0>(thread)->run = true;
        std::get<0>(thread)->doStep_ = true;

        while (!std::get<0>(thread)->stepDone_)
        {
          std::chrono::milliseconds dura(20);
          std::this_thread::sleep_for(dura);
        }
      }

      allDoneNoResult = true;

      //check if we found a result or all threads are done and we found no result
      for (successIndex = 0; successIndex < results.size(); successIndex++)
      {
        int res = 0;
        {
          std::lock_guard<std::mutex> lk(chooseSearchResultMutex);
          res = results[successIndex];
        }

        if (res == 1)
        {
          found = true;
          break;
        }
        else if (res == 0)
        {
          //std::get<0>(threads[successIndex])->stepDone_ = true;
        }
        else
        {
          allDoneNoResult = false;
        }
      }
    }
    while (!found && !allDoneNoResult);

    Any rc;
    if (found)
    {
//      for (size_t i = 0; i < results.size(); i++)
//      {
//        if (results[i] == 1)
//        {
          if (std::get<0>(threads[successIndex])->children_.size() == 0)
          {
            auto container = std::make_shared<BfsDataContainer>();
            container->setState(
                DatabaseManager::getInstance().getCloneWithNewName(
                    std::get<0>(threads[successIndex])->getDb()->getDbName(),
                    "DB_" + std::to_string(getNowTicks())));

            for (const auto& choice : std::get<0>(threads[successIndex])->choices_)
            {
              container->addChoice(choice);
            }

            bfsStatesQueue->push_back(container);
          }
//        }
//      }

      this->choices_ = std::get<0>(threads[successIndex])->choices_;

      if (CommandLineArgsContainer::getInstance().getShowDebugMessages()
          || (!this->isSearch_ && this->name_ != "reproduceStateVisitor"))
      {
        std::lock_guard<std::mutex> lk(coutMutex);
        std::cout << ">>>> " << msgPrefix_ << "Found valid block in 'choose'! Picked block number "
            << successIndex + 1 << std::endl;
      }

      rc = Any { true };
    }
    else
    {
      rc = Any { false };
    }

    for (auto& thread : threads)
    {
      std::get<0>(thread)->cancelled_ = true;
      std::get<0>(thread)->stepDone_ = true;
    }

    for (auto& thread : threads)
    {
      std::get<1>(thread).join();
    }

    return rc;
  }
}

Any ActionProcedureInterpretationVisitor::visit(NodePick& pick)
{
  auto fluentName = pick.getSetExpr()->accept(*this).get<std::string>();
  auto complete_set = db_->executeQuery(
      SQLGenerator::getInstance().getSqlStringSelectAll(fluentName));

  //TODO make it more perfoming through usage of db query
  //pick a value for each unbound variable in varTuple, leave the bound variables as they are
  // get the already assigned elements
  auto varTuple = pick.getTuple()->accept(*this).get<std::vector<std::string>>();
  std::vector<std::pair<size_t, std::string>> assigned_elements;
  for (size_t i = 0; i != varTuple.size(); i++)
  {
    if (varTuple[i][0] == '$') // TODO make this clean with classes (indicate for a variable)
    {
      if (getVarTable()->variableExists(varTuple[i])
          && getVarTable()->isVariableInitialized(varTuple[i]))
        assigned_elements.push_back(
            std::pair<size_t, std::string>(i, getVarTable()->getVariableValue(varTuple[i])));
    }
    else
      assigned_elements.push_back(std::pair<size_t, std::string>(i, varTuple[i]));
  }

  std::vector<std::vector<std::string>> set;
  // use only tuples complient with the assigned elements
  for (const auto& tuple : complete_set)
  {
    if (tuple.size() != varTuple.size())
      throw std::runtime_error(
          "size of tuple for luent " + fluentName + " does not match varible tuple size in pick");
    bool keep_tuple = true;
    for (const auto& assigned_element : assigned_elements)
    {
      if (tuple[assigned_element.first] != assigned_element.second)
      {
        keep_tuple = false;
        break;
      }
    }
    if (keep_tuple)
      set.push_back(tuple);
  }

  if (set.empty())
  {
    if (CommandLineArgsContainer::getInstance().getShowDebugMessages()
        || (!this->isSearch_ && this->name_ != "reproduceStateVisitor"))
    {
      std::cout << ">>>> " << msgPrefix_ << "can't pick a value for value " << fluentName << "..."
          << std::endl;
    }
    return Any { false };
  }

  if (!isSearch_)
  {
    int idx = -1;
    if (choicesForOnlineExecution.empty())
    {
      //XXX: HACKHACK if we reproduce state in BFS we execute all choices known
      //and stop if we ran out of choices, i.e. choicesForOnlineExecution is empty!
      if (this->name_ == "reproduceStateVisitor")
      {
        return Any { false };
      }

      RandomNumberGenerator rng;
      idx = rng.getRandomNumber(0, set.size() - 1);
    }
    else
    {
      idx = choicesForOnlineExecution.at(0);
      choicesForOnlineExecution.erase(std::begin(choicesForOnlineExecution));
    }

    if (CommandLineArgsContainer::getInstance().getShowDebugMessages()
        || (!this->isSearch_ && this->name_ != "reproduceStateVisitor"))
    {
      std::cout << ">>>> " << msgPrefix_ << "Picking value " << tupleToString(set[idx]) << "..."
          << std::endl;
    }

    return runBlockForPickedTuple(pick, set, idx, *this);
  }
  else
  {
    std::vector<std::tuple<std::shared_ptr<ActionProcedureInterpretationVisitor>, std::thread>> threads;
    std::vector<int> results;
    std::mutex pickSearchResultMutex;

    std::shared_ptr<ActionProcedureInterpretationVisitor> v = nullptr;

    for (size_t idx = 0; idx < set.size(); idx++)
    {
      //Fire up a temporary db, temporary varTable and search for sequence of actions
      std::string name = "<search " + std::to_string(idx + 1) + ", picking "
          + tupleToString(set[idx]) + ">";
      auto tempDB = DatabaseManager::getInstance().getCloneWithNewName(db_->getDbName(),
          name + "DB_" + std::to_string(getNowTicks()));

      std::string tempVarTableName = name + "VarTable_" + std::to_string(getNowTicks());
      auto& tempVarTable = VariableTableManager::getInstance().getCloneWithNewName(
          varTable_->getName(), tempVarTableName);
      if(set[idx].size() != varTuple.size())
        throw std::runtime_error("size of picked tuple does not corespond to size of variables");

      for(size_t i = 0; i < set[idx].size(); ++i)
        tempVarTable.addVariable(varTuple[i], set[idx][i]);

      auto formulaEvaluator = std::make_shared<FormulaEvaluator>(&tempVarTable, tempDB.get());

      v = std::make_shared<ActionProcedureInterpretationVisitor>(formulaEvaluator, tempDB,
          BackendFactory::getInstance().getBackend()->getSignalHandler(), tempVarTable, true, name);

      v->choices_ = this->choices_;
      v->choices_.push_back(idx);
      this->children_.push_back(v);

      {
        std::lock_guard<std::mutex> lk(pickSearchResultMutex);
        results.push_back(-1);
      }

      std::thread t([&pick,&set,idx,v,&results, &pickSearchResultMutex]()
      {
        while(!v->run)
        {
          std::chrono::milliseconds dura(20);
          std::this_thread::sleep_for(dura);
        }

        auto ret = v->runBlockForPickedTuple(pick, set, idx,*v.get());

        {
          std::lock_guard<std::mutex> lk(pickSearchResultMutex);
          results[idx] = ret.get<bool>() ? 1 : 0;
        }

        v->stepDone_ = true;

      });
      threads.push_back(std::make_tuple(v, std::move(t)));
    }

    size_t successIndex = 0;
    bool found = false;
    bool allDoneNoResult = true;

    do
    {
      for (auto& thread : threads)
      {
        std::get<0>(thread)->run = true;
        std::get<0>(thread)->doStep_ = true;

        while (!std::get<0>(thread)->stepDone_)
        {
          std::chrono::milliseconds dura(20);
          std::this_thread::sleep_for(dura);
        }
      }

      allDoneNoResult = true;

      //check if we found a result or all threads are done and we found no result
      for (successIndex = 0; successIndex < results.size(); successIndex++)
      {
        int res;
        {
          std::lock_guard<std::mutex> lk(pickSearchResultMutex);
          res = results[successIndex];
        }

        if (res == 1)
        {
          found = true;
          break;
        }
        else if (res == 0)
        {
          //std::get<0>(threads[successIndex])->stepDone_ = true;
        }
        else
        {
          allDoneNoResult = false;
        }
      }
    }
    while (!found && !allDoneNoResult);

    Any rc;
    if (found)
    {
//      for (size_t i = 0; i < results.size(); i++)
//      {
//        if (results[i] == 1)
//        {
          if (std::get<0>(threads[successIndex])->children_.size() == 0)
          {
            auto container = std::make_shared<BfsDataContainer>();
            container->setState(
                DatabaseManager::getInstance().getCloneWithNewName(
                    std::get<0>(threads[successIndex])->getDb()->getDbName(),
                    "DB_" + std::to_string(getNowTicks())));

            for (const auto& choice : std::get<0>(threads[successIndex])->choices_)
            {
              container->addChoice(choice);
            }

            bfsStatesQueue->push_back(container);
          }
//        }
//      }

	  if (CommandLineArgsContainer::getInstance().getShowDebugMessages()
		  || (!this->isSearch_ && this->name_ != "reproduceStateVisitor"))
	  {
		  for (const auto& choice : this->choices_)
			  std::cout << "have choices before pick " << choice << std::endl;
	  }

	  this->choices_ = std::get<0>(threads[successIndex])->choices_;

      if (CommandLineArgsContainer::getInstance().getShowDebugMessages()
          || (!this->isSearch_ && this->name_ != "reproduceStateVisitor"))
      {
		  for (const auto& choice : this->choices_)
			  std::cout << "have choices after pick " << choice << std::endl;
      }

      if (CommandLineArgsContainer::getInstance().getShowDebugMessages()
          || (!this->isSearch_ && this->name_ != "reproduceStateVisitor"))
      {
        std::cout << ">>>> " << msgPrefix_ << "Found valid 'pick' value! Picked "
            << tupleToString(set[successIndex]) << std::endl;
      }

      rc = Any { true };
    }
    else
    {
      rc = Any { false };
    }

    for (auto& thread : threads)
    {
      std::get<0>(thread)->cancelled_ = true;
      std::get<0>(thread)->stepDone_ = true;
    }

    for (auto& thread : threads)
    {
      std::get<1>(thread).join();
    }

    return rc;
  }

}

Any ActionProcedureInterpretationVisitor::runBlockForPickedTuple(const NodePick& pickNode,
    std::vector<std::vector<std::string>> set, int tupleIndex,
    ActionProcedureInterpretationVisitor& ctx)
{
  auto varTuple = pickNode.getTuple()->accept(ctx).get<std::vector<std::string>>();
  auto fluentName = pickNode.getSetExpr()->accept(ctx).get<std::string>();

  ctx.getVarTable()->addScope();

//pick a value for each unbound variable in varTuple, leave the bound variables as they are
  for (size_t i = 0; i != varTuple.size(); i++)
  {
    if (!ctx.getVarTable()->variableExists(varTuple[i])
        || !ctx.getVarTable()->isVariableInitialized(varTuple[i]))
    {
      ctx.getVarTable()->addVariable(varTuple[i], set[tupleIndex][i]);
    }
  }

  auto stmts = pickNode.getBlock()->getStatements();
  bool success = true;
  for (const auto& stmt : stmts)
  {
    auto ret = stmt->accept(ctx);
    if (ret.hasType<bool>())
    {
      success = success && ret.get<bool>();
    }

    if (!success)
    {
      break;
    }
  }

  ctx.getVarTable()->removeScope();

//Cleanup shadow fluent in case it is one
  if (isShadowFluent(fluentName, *ctx.getDb().get()))
  {
    cleanupShadowFluent(fluentName, *ctx.getDb().get());
  }

  return Any { success };
}

Any ActionProcedureInterpretationVisitor::visit(NodeIncompleteKnowledge& incompleteKnowledge)
{
  throw std::runtime_error("Incomplete knowledge is not implemented!");
}

Any ActionProcedureInterpretationVisitor::visit(NodePatternMatching& patternMatching)
{
  throw std::runtime_error("Pattern matching note should have been rewritten at this point!");
}

void ActionProcedureInterpretationVisitor::consumeExoEventData(const std::string& eventName,
    const std::unordered_map<std::string, std::string>& variablesAndValues)
{
  std::lock_guard<std::mutex> lock(exoEventDataBufferMutex_);
  exoEventDataBuffer_.push(std::make_tuple(eventName, variablesAndValues));
}

void ActionProcedureInterpretationVisitor::applyExoEventData()
{
  std::lock_guard<std::mutex> lock(exoEventDataBufferMutex_);

  while (exoEventDataBuffer_.size())
  {
    auto exoEventData = exoEventDataBuffer_.front();
    exoEventDataBuffer_.pop();

    auto exoEventName = std::get<0>(exoEventData);
    auto argMap = std::get<1>(exoEventData);
    auto exoEventProg = ExecutableElementsContainer::getInstance().getExoEvent(exoEventName,
        argMap.size());

    if (exoEventProg == nullptr)
    {
      std::cout << "[WARNING]: ignore exogen event with name: " << exoEventName
          << " as it is not defined " << std::endl;
      continue;
    }

    varTable_->addScope();

    std::vector<std::string> paramList;
    if (auto paramNodeList = exoEventProg->getArgList())
    {
      paramList = paramNodeList->accept(*this).get<std::vector<std::string>>();
    }

    //set param values for action call
    for (size_t i = 0; i != paramList.size(); i++)
    {
      varTable_->addVariable(paramList[i], argMap[paramList[i]]); //TODO: what if param names/count is no the same?
    }

    exoEventProg->accept(*this);

    varTable_->removeScope();
  }
}

} /* namespace execution */
} /* namespace yagi */
