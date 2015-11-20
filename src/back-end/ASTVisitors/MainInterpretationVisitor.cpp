/**
 * @file   MainInterpretationVisitor.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Responsible for executing a YAGI program, i.e. the main interpretation visitor is
 * directly invoked from the GUI, i.e. it is the main entry point of the execution of a YAGI program.
 * It either redirects execution to a ActionProcedureInterpretation visitor instance or executes
 * directly if the execution semantics differ from the semantics of the ActionProcedureInterpretation
 * implementation
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


#include "MainInterpretationVisitor.h"

#include "../../utils/ToStringHelper.h"
#include "../Database/DatabaseManager.h"
#include "../ExecutableElementsContainer.h"
#include "../SQLGenerator.h"
#include "ActionProcedureInterpretationVisitor.h"
#include "../Formulas/FormulaEvaluator.h"
#include "../Variables/VariableTableManager.h"
#include "../BackendFactory.h"

using yagi::database::DatabaseManager;

using namespace yagi::formula;

namespace yagi {
namespace execution {

MainInterpretationVisitor::MainInterpretationVisitor()
{
  initDB();
}

MainInterpretationVisitor::~MainInterpretationVisitor()
{

}

void MainInterpretationVisitor::initDB()
{
  auto db = DatabaseManager::getInstance().getMainDB();

  if (!db->executeQuery(
      SQLGenerator::getInstance().getSqlStringExistsTable(
          SQLGenerator::getInstance().FACTS_TABLE_NAME_)).size())
  {
    db->executeNonQuery(SQLGenerator::getInstance().getSqlStringCreateFactsTable());
  }

  if (!db->executeQuery(
      SQLGenerator::getInstance().getSqlStringExistsTable(
          SQLGenerator::getInstance().SHADOW_FLUENTS_TABLE_NAME_)).size())
  {
    db->executeNonQuery(SQLGenerator::getInstance().getSqlStringCreateShadowFluentsTable());
  }

}

Any MainInterpretationVisitor::visit(NodeID& id)
{
  // std::cout << "main interpreter id called" << std::endl;

  ActionProcedureInterpretationVisitor v;
  return v.visit(id);
}

Any MainInterpretationVisitor::visit(NodeFluentDecl& fluentDecl)
{
  // std::cout << "main interpreter fluent decl called" << std::endl;

  ActionProcedureInterpretationVisitor v(DatabaseManager::getInstance().getMainDB());
  return v.visit(fluentDecl);
}

Any MainInterpretationVisitor::visit(NodeFactDecl& factDecl)
{
  // std::cout << "main interpreter fact decl called" << std::endl;

  ActionProcedureInterpretationVisitor apiv;
  auto db = DatabaseManager::getInstance().getMainDB();
  auto tableName = factDecl.getFactName()->accept(*this).get<std::string>();

  std::vector<std::vector<std::string>> domains;
  for (const auto& domainNode : factDecl.getDomains())
  {
    auto vec = domainNode->accept(apiv).get<std::vector<std::string>>();
    domains.push_back(vec);
  }

  auto sqlStrings = SQLGenerator::getInstance().getSqlStringsCreateTableAndDomains(tableName,
      domains);

  for (const auto& sqlString : sqlStrings)
  {
    db->executeNonQuery(sqlString);
  }

  //store in db that it is a fact
//  if (!db->executeQuery(
//      SQLGenerator::getInstance().getSqlStringExistsTable(
//          SQLGenerator::getInstance().FACTS_TABLE_NAME_)).size())
//  {
//    db->executeNonQuery(SQLGenerator::getInstance().getSqlStringCreateFactsTable());
//  }
  db->executeNonQuery(SQLGenerator::getInstance().getSqlStringAddFact(factDecl));

  return Any { };
}

Any MainInterpretationVisitor::visit(NodeFluentQuery& fluentQuery)
{
  // std::cout << "main interpreter fluent query called" << std::endl;

  auto db = DatabaseManager::getInstance().getMainDB();
  auto fluentName = fluentQuery.getFluentToQueryName()->accept(*this).get<std::string>();

  if (!db->executeQuery(SQLGenerator::getInstance().getSqlStringExistsTable(fluentName)).size())
  {
    std::cout << ">>>> Fluent/Fact '" + fluentName + "' does not exist!" << std::endl;
  }
  else
  {
    auto fluentState = db->executeQuery(
        SQLGenerator::getInstance().getSqlStringSelectAll(fluentName));
    auto str = yagi::fluentDBDataToString(fluentState);

    std::cout << ">>>> " << fluentName << " = " << str << std::endl;
  }

  return Any { };
}

Any MainInterpretationVisitor::visit(NodeIDAssignment& idAssign)
{
  // std::cout << "main interpreter id assignement called" << std::endl;

  auto formulaEvaluator = std::make_shared<FormulaEvaluator>(
      &VariableTableManager::getInstance().getMainVariableTable(),
      DatabaseManager::getInstance().getMainDB().get());

  ActionProcedureInterpretationVisitor v(formulaEvaluator,
      DatabaseManager::getInstance().getMainDB(), BackendFactory::getInstance().getBackend()->getSignalHandler(),
      VariableTableManager::getInstance().getMainVariableTable());

  return v.visit(idAssign);
}

Any MainInterpretationVisitor::visit(NodeSearch& nodeSearch)
{
  // std::cout << "main interpreter search called" << std::endl;

  auto formulaEvaluator = std::make_shared<FormulaEvaluator>(
      &VariableTableManager::getInstance().getMainVariableTable(),
      DatabaseManager::getInstance().getMainDB().get());

  ActionProcedureInterpretationVisitor v(formulaEvaluator,
      DatabaseManager::getInstance().getMainDB(), BackendFactory::getInstance().getBackend()->getSignalHandler(),
      VariableTableManager::getInstance().getMainVariableTable());

  return v.visit(nodeSearch);
}

Any MainInterpretationVisitor::visit(NodeExogenousEventDecl& nodeExoEventDecl)
{
  // std::cout << "main interpreter exogenious event decl called" << std::endl;

  ExecutableElementsContainer::getInstance().addOrReplaceExoEvent(nodeExoEventDecl);
  return Any { };
}

Any MainInterpretationVisitor::visit(NodeActionDecl& actionDecl)
{
  // std::cout << "main interpreter action decl called" << std::endl;

  ExecutableElementsContainer::getInstance().addOrReplaceAction(actionDecl);
  return Any { };
}

Any MainInterpretationVisitor::visit(NodeProcDecl& procDecl)
{
  // std::cout << "main interpreter proc decl called" << std::endl;

  ExecutableElementsContainer::getInstance().addOrReplaceProcedure(procDecl);
  return Any { };
}

Any MainInterpretationVisitor::visit(NodeProcExecution& procExec)
{
  // std::cout << "main interpreter procedure execution called" << std::endl;

  auto formulaEvaluator = std::make_shared<FormulaEvaluator>(
      &VariableTableManager::getInstance().getMainVariableTable(),
      DatabaseManager::getInstance().getMainDB().get());

  ActionProcedureInterpretationVisitor v(formulaEvaluator,
      DatabaseManager::getInstance().getMainDB(), BackendFactory::getInstance().getBackend()->getSignalHandler(),
      VariableTableManager::getInstance().getMainVariableTable());

  return Any { v.visit(procExec) };
}

Any MainInterpretationVisitor::visit(NodeSet& set)
{
  // std::cout << "main interpreter set called" << std::endl;

  ActionProcedureInterpretationVisitor v;
  return v.visit(set);
}

Any MainInterpretationVisitor::visit(NodeTuple& tuple)
{
  // std::cout << "main interpreter tuple called" << std::endl;

  ActionProcedureInterpretationVisitor v;
  return v.visit(tuple);
}

Any MainInterpretationVisitor::visit(NodeVariable& variable)
{
  // std::cout << "main interpreter variable called" << std::endl;

  ActionProcedureInterpretationVisitor apiv;
  return apiv.visit(variable);
}

Any MainInterpretationVisitor::visit(NodeVariableAssignment& varAss)
{
  // std::cout << "main interpreter assignement called" << std::endl;

  ActionProcedureInterpretationVisitor apiv(
      VariableTableManager::getInstance().getMainVariableTable());
  return apiv.visit(varAss);
}

Any MainInterpretationVisitor::visit(NodeString& str)
{
  // std::cout << "main interpreter string called" << std::endl;

  ActionProcedureInterpretationVisitor apiv;
  return apiv.visit(str);
}

Any MainInterpretationVisitor::visit(NodeSetExpression& setExpr)
{
  // std::cout << "main interpreter set expr called" << std::endl;

  ActionProcedureInterpretationVisitor v;
  return v.visit(setExpr);
}

Any MainInterpretationVisitor::visit(NodeForLoop& forLoop)
{
  // std::cout << "main interpreter for loop called" << std::endl;

  auto formulaEvaluator = std::make_shared<FormulaEvaluator>(
      &VariableTableManager::getInstance().getMainVariableTable(),
      DatabaseManager::getInstance().getMainDB().get());

  ActionProcedureInterpretationVisitor v(formulaEvaluator,
      DatabaseManager::getInstance().getMainDB(), BackendFactory::getInstance().getBackend()->getSignalHandler(),
      VariableTableManager::getInstance().getMainVariableTable());

  return v.visit(forLoop);
}

Any MainInterpretationVisitor::visit(NodeConditional& conditional)
{
  // std::cout << "main interpreter conditional called" << std::endl;

  auto formulaEvaluator = std::make_shared<FormulaEvaluator>(
      &VariableTableManager::getInstance().getMainVariableTable(),
      DatabaseManager::getInstance().getMainDB().get());

  ActionProcedureInterpretationVisitor v(formulaEvaluator,
      DatabaseManager::getInstance().getMainDB(), BackendFactory::getInstance().getBackend()->getSignalHandler(),
      VariableTableManager::getInstance().getMainVariableTable());

  return v.visit(conditional);
}

Any MainInterpretationVisitor::visit(NodeTest& nodeTest)
{
  // std::cout << "main interpreter test called" << std::endl;
  auto formulaEvaluator = std::make_shared<FormulaEvaluator>(
      &VariableTableManager::getInstance().getMainVariableTable(),
      DatabaseManager::getInstance().getMainDB().get());

  ActionProcedureInterpretationVisitor v(formulaEvaluator,
      DatabaseManager::getInstance().getMainDB(), BackendFactory::getInstance().getBackend()->getSignalHandler(),
      VariableTableManager::getInstance().getMainVariableTable());

  return v.visit(nodeTest);
}

Any MainInterpretationVisitor::visit(NodeChoose& nodeChoose)
{
  // std::cout << "main interpreter choose called" << std::endl;

  auto formulaEvaluator = std::make_shared<FormulaEvaluator>(
      &VariableTableManager::getInstance().getMainVariableTable(),
      DatabaseManager::getInstance().getMainDB().get());

  ActionProcedureInterpretationVisitor v(formulaEvaluator,
      DatabaseManager::getInstance().getMainDB(), BackendFactory::getInstance().getBackend()->getSignalHandler(),
      VariableTableManager::getInstance().getMainVariableTable());

  return v.visit(nodeChoose);
}

Any MainInterpretationVisitor::visit(NodePick& nodePick)
{
  // std::cout << "main interpreter pick called" << std::endl;

  auto formulaEvaluator = std::make_shared<FormulaEvaluator>(
      &VariableTableManager::getInstance().getMainVariableTable(),
      DatabaseManager::getInstance().getMainDB().get());

  ActionProcedureInterpretationVisitor v(formulaEvaluator,
      DatabaseManager::getInstance().getMainDB(), BackendFactory::getInstance().getBackend()->getSignalHandler(),
      VariableTableManager::getInstance().getMainVariableTable());

  return v.visit(nodePick);
}

Any MainInterpretationVisitor::visit(NodeWhileLoop& nodeWhileLoop)
{
  // std::cout << "main interpreter while called" << std::endl;

  auto formulaEvaluator = std::make_shared<FormulaEvaluator>(
      &VariableTableManager::getInstance().getMainVariableTable(),
      DatabaseManager::getInstance().getMainDB().get());

  ActionProcedureInterpretationVisitor v(formulaEvaluator,
      DatabaseManager::getInstance().getMainDB(), BackendFactory::getInstance().getBackend()->getSignalHandler(),
      VariableTableManager::getInstance().getMainVariableTable());

  return v.visit(nodeWhileLoop);
}

}/* namespace execution */
} /* namespace yagi */

