/*
 * ActionProcedureInterpretationVisitor.cpp
 *
 *  Created on: Jul 19, 2014
 *      Author: cmaier
 */

#include "ActionProcedureInterpretationVisitor.h"

#include <memory>
#include <unordered_map>

#include "../../common/ASTNodeTypes/Domains/NodeDomainStringElements.h"
#include "../Database/DatabaseConnectorBase.h"
#include "../ExecutableElementsContainer.h"
#include "../SQLGenerator.h"
#include "../Signals/IYAGISignalHandler.h"
#include "../Formulas/IFormulaEvaluator.h"
#include "../../utils/SetOperations.h"
#include "../TreeHelper.h"
#include "../../utils/RandomNumberGenerator.h"
#include "../Database/DatabaseManager.h"
#include "../Database/DBHelper.h"
#include "../Formulas/FormulaEvaluator.h"
#include "../Signals/CoutCinSignalHandler.h"
#include "../Variables/VariableTable.h"
#include "../Variables/VariableTableManager.h"

using yagi::database::DatabaseConnectorBase;
using yagi::execution::IYAGISignalHandler;
using yagi::formula::FormulaEvaluator;
using yagi::formula::IFormulaEvaluator;

namespace yagi {
namespace execution {

ActionProcedureInterpretationVisitor::ActionProcedureInterpretationVisitor() :
    formulaEvaluator_(nullptr), db_(nullptr), signalReceiver_(nullptr), varTable_(nullptr)
{

}

ActionProcedureInterpretationVisitor::ActionProcedureInterpretationVisitor(
    std::shared_ptr<DatabaseConnectorBase> db) :
    formulaEvaluator_(nullptr), db_(db), signalReceiver_(nullptr), varTable_(nullptr)
{
}

ActionProcedureInterpretationVisitor::ActionProcedureInterpretationVisitor(
    std::shared_ptr<IFormulaEvaluator> formulaEvaluator, std::shared_ptr<DatabaseConnectorBase> db,
    std::shared_ptr<IYAGISignalHandler> signalReceiver, VariableTable& varTable) :
    formulaEvaluator_(formulaEvaluator), db_(db), signalReceiver_(signalReceiver), varTable_(
        &varTable)
{
  formulaEvaluator_->setContext(this);
}

ActionProcedureInterpretationVisitor::~ActionProcedureInterpretationVisitor()
{

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
  return triggerYagiSignal(signal, std::vector<std::string> { });
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

    //'test' statement returns wether or not it holds
    if (auto isTest = std::dynamic_pointer_cast<NodeTest>(stmt))
    {
      if (!ret.empty() && ret.hasType<bool>())
      {
        std::string outText = "holds!";
        if (!ret.get<bool>())
        {
          outText = "does NOT hold!";
        }

        std::cout << "Test condition in procedure '" << procName << "' " << outText << std::endl;

        if (!ret.get<bool>())
          break;
      }
    }
  }

  return Any { };
}

Any ActionProcedureInterpretationVisitor::visit(NodeActionDecl& actionDecl)
{
  auto actionName = actionDecl.getActionName()->accept(*this).get<std::string>();

  if (auto ap = actionDecl.getActionPrecondition())
  {
    bool apHolds = ap->accept(*this).tryGetCopy<bool>(false);
    if (!apHolds)
    {
      std::cout << "--> AP for action '" + actionName + "' does NOT hold." << std::endl;

      return Any { false };
    }

    std::cout << "--> AP for action '" + actionName + "' holds." << std::endl;
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
  auto tempVarTable = VariableTableManager::getInstance().getVariableTable(tempVarTableName);

  auto formulaEvaluator = std::make_shared<FormulaEvaluator>(&tempVarTable, tempDB.get());

  ActionProcedureInterpretationVisitor v(formulaEvaluator, tempDB,
      std::make_shared<CoutCinSignalHandler>(), tempVarTable);

  auto searchRetVal = search.getBlock()->accept(v);

  if (searchRetVal.get<bool>())
  {
    std::cout << ">>>> search found valid path! Executing..." << std::endl;

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
  bool procExecRetVal;

  std::vector<std::string> argList { };
  if (auto paramNode = procExec.getParameters())
  {
    argList = paramNode->accept(*this).get<std::vector<std::string>>();
  }

  varTable_->addScope();

  std::vector<std::string> paramList { };
  if (auto actionToExecute = ExecutableElementsContainer::getInstance().getAction(actionOrProcName))
  {
    if (auto paramNodeList = actionToExecute->getVarList())
    {
      paramList = paramNodeList->accept(*this).get<std::vector<std::string>>();
    }

    //set param values for action call
    for (auto i = 0; i != paramList.size(); i++)
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
  }
  else if (auto procToExecute = ExecutableElementsContainer::getInstance().getProcedure(
      actionOrProcName))
  {
    if (auto paramNodeList = procToExecute->getArgList())
    {
      paramList = paramNodeList->accept(*this).get<std::vector<std::string>>();
    }

    //set param values for action call
    for (auto i = 0; i != paramList.size(); i++)
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

  varTable_->removeScope();

  return Any { procExecRetVal };
}

Any ActionProcedureInterpretationVisitor::visit(NodeAssignmentOperator& assOp)
{
  return Any { assOp.getOperator() };
}

Any ActionProcedureInterpretationVisitor::visit(NodeIDAssignment& idAssign)
{
  auto lhs = idAssign.getFluentName()->accept(*this).get<std::string>();

  //the rhs is a (shadow-)fluent/fact for sure, so we get the name here
  auto rhs = idAssign.getSetExpr()->accept(*this).get<std::string>();
  auto assignOp = idAssign.getOperator()->accept(*this).get<AssignmentOperator>();

  if (assignOp == AssignmentOperator::Unknown)
  {
    throw std::runtime_error("Unknown assign operator!");
  }

  if (assignOp == AssignmentOperator::Assign)
  {
    db_->executeNonQuery(SQLGenerator::getInstance().getSqlStringClearTable(lhs));
  }

  //get data from rhs
  auto data = db_->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll(rhs));
  auto sqlStrings = SQLGenerator::getInstance().getSqlStringsForIDAssign(lhs, data, assignOp);

  std::for_each(std::begin(sqlStrings), std::end(sqlStrings), [this](const std::string& stmt)
  {
    db_->executeNonQuery(stmt);
  });

  return Any { };
}

Any ActionProcedureInterpretationVisitor::visit(NodeFluentDecl& fluentDecl)
{
  auto tableName = fluentDecl.getFluentName()->accept(*this).get<std::string>();

  db_->executeNonQuery(
      SQLGenerator::getInstance().getSqlStringCreateTable(tableName,
          fluentDecl.getDomains().size()));
  return Any { };
}

Any ActionProcedureInterpretationVisitor::visit(NodeSet& set)
{
  //Build shadow fluent for set
  std::vector<std::vector<std::string>> valueSet;
  std::vector<std::vector<std::string>> domains;

  auto tuples = set.getTuples();

  //build strings to add to the DB and deduce domains
  bool first = true;
  std::for_each(std::begin(tuples), std::end(tuples),
      [this, &valueSet, &domains, &first](const std::shared_ptr<NodeTuple>& nodeTuple)
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

        int idx=0;

        //add values to respective domains
        std::for_each(std::begin(vals), std::end(vals),
            [&domains,&idx,&first](const std::string& str)
            {
              if (!first)
              {
                domains[idx].push_back(str);
              }
              else
              {
                domains.push_back(
                    { str});
              }

              idx++;
            });

        first = false;
      });

  //save shadow fluent to db
  auto shadowFluentName = "shadow" + std::to_string(getNowTicks());

  NodeFluentDecl shadowFluentNode;
  shadowFluentNode.setFluentName(std::make_shared<NodeID>(shadowFluentName));

  std::for_each(std::begin(domains), std::end(domains),
      [this, &shadowFluentNode](const std::vector<std::string>& domain)
      {
        auto domainNode = std::make_shared<NodeDomainStringElements>();

        std::for_each(std::begin(domain), std::end(domain),
            [&domainNode](const std::string& str)
            {
              domainNode->addStringToDomain(std::make_shared<NodeString>(str));
            });

        shadowFluentNode.addDomain(domainNode);
      });

  visit(shadowFluentNode);

  //assign
  auto sqlStrings = SQLGenerator::getInstance().getSqlStringsForIDAssign(shadowFluentName, valueSet,
      AssignmentOperator::Assign);

  std::for_each(std::begin(sqlStrings), std::end(sqlStrings), [this](const std::string& stmt)
  {
    db_->executeNonQuery(stmt);
  });

  //add the info the that fluent is a shadow fluent
  if (!db_->executeQuery(
      SQLGenerator::getInstance().getSqlStringExistsTable(
          SQLGenerator::getInstance().SHADOW_FLUENTS_TABLE_NAME_)).size())
  {
    db_->executeNonQuery(SQLGenerator::getInstance().getSqlStringCreateShadowFluentsTable());
  }

  db_->executeNonQuery(
      SQLGenerator::getInstance().getSqlStringMakeTableShadowFluent(shadowFluentName));

  return Any { shadowFluentName };
}

Any ActionProcedureInterpretationVisitor::visit(NodeTuple& tuple)
{
  //Build vector with tuple values
  std::vector<std::string> tupleVals;

  auto values = tuple.getTupleValues();

  std::for_each(std::begin(values), std::end(values),
      [this, &tupleVals](const std::shared_ptr<ASTNodeBase<>>& value)
      {
        auto val = value->accept(*this).get<std::string>();
        tupleVals.push_back(val);
      });

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
    lhsResult = yagi::treeHelper::getValueFromValueNode(lhs.get(), *this, varTable_);
  }

  if (auto rhs = valExpr.getRhs())
  {
    rhsResult = yagi::treeHelper::getValueFromValueNode(rhs.get(), *this, varTable_);
  }

  if (auto op = valExpr.getOperator())
  {
    exprOp = op->getOperator();
  }
  else
  {
    return Any { lhsResult };
  }

  if (exprOp == ExprOperator::Plus)
  {
    return Any { lhsResult + rhsResult };
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

  while (whileLoop.getFormula()->accept(*this).get<bool>())
  {
    std::for_each(std::begin(statements), std::end(statements),
        [this](const std::shared_ptr<NodeStatementBase>& stmt)
        {
          stmt->accept(*this);
        });
  }
  return Any { };
}

Any ActionProcedureInterpretationVisitor::visit(NodeTest& test)
{
  //return test condition result to handle it in proc execution
  return Any { test.getFormula()->accept(*this).get<bool>() };
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
    varTable_->addVariable(varName);
  }

  //set values to variables and execute <block>
  for (const auto& tuple : set)
  {
    for (auto i = 0; i != tuple.size(); i++)
    {
      varTable_->setVariable(varTuple[i], tuple[i]);
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
    statements = conditional.getElseBlock()->getStatements();
  }

  std::for_each(std::begin(statements), std::end(statements),
      [this](const std::shared_ptr<NodeStatementBase>& stmt)
      {
        stmt->accept(*this);
      });

  return Any { };
}

Any ActionProcedureInterpretationVisitor::visit(NodeChoose& choose)
{
  auto blocks = choose.getBlocks();

  RandomNumberGenerator rng;
  int randomIndex = rng.getRandomNumber(0, blocks.size() - 1);

  auto stmts = blocks.at(randomIndex)->getStatements();

  for (const auto& stmt : stmts)
  {
    stmt->accept(*this);
  }

  return Any { };
}

Any ActionProcedureInterpretationVisitor::visit(NodePick& pick)
{
  auto varTuple = pick.getTuple()->accept(*this).get<std::vector<std::string>>();
  auto fluentName = pick.getSetExpr()->accept(*this).get<std::string>();

  auto set = db_->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll(fluentName));

  RandomNumberGenerator rng;
  int randomIndex = rng.getRandomNumber(0, set.size() - 1);

  varTable_->addScope();

  //pick a value for each unbound variable in varTuple, leave the bound variables as they are
  for (auto i = 0; i != varTuple.size(); i++)
  {
    if (!varTable_->variableExists(varTuple[i]) || !varTable_->isVariableInitialized(varTuple[i]))
    {
      varTable_->addVariable(varTuple[i], set[randomIndex][i]);
    }
  }

  auto stmts = pick.getBlock()->getStatements();
  for (const auto& stmt : stmts)
  {
    stmt->accept(*this);
  }

  varTable_->removeScope();

  //Cleanup shadow fluent in case it is one
  if (isShadowFluent(fluentName, *db_.get()))
  {
    cleanupShadowFluent(fluentName, *db_.get());
  }

  return Any { };
}

} /* namespace execution */
} /* namespace yagi */
