/*
 * MainInterpretationVisitor.cpp
 *
 *  Created on: Jul 9, 2014
 *      Author: cmaier
 */

#include "MainInterpretationVisitor.h"

#include "../../utils/ToStringHelper.h"
#include "../Database/DatabaseManager.h"
#include "../ExecutableElementsContainer.h"
#include "../SQLGenerator.h"
#include "ActionProcedureInterpretationVisitor.h"
#include "../Formulas/FormulaEvaluator.h"
#include "../Variables/VariableTableManager.h"
#include "../Signals/CoutCinSignalHandler.h"

using yagi::database::DatabaseManager;

using namespace yagi::formula;

namespace yagi {
namespace execution {

MainInterpretationVisitor::MainInterpretationVisitor()
{

}

MainInterpretationVisitor::~MainInterpretationVisitor()
{

}

Any MainInterpretationVisitor::visit(NodeID& id)
{
  ActionProcedureInterpretationVisitor v;
  return v.visit(id);
}

Any MainInterpretationVisitor::visit(NodeProgram& program)
{
  std::for_each(program.getProgram().begin(), program.getProgram().end(),
      [this](std::shared_ptr<ASTNodeBase<>> stmt)
      {
        //safety net to check if only valid YAGI lines and not any
        //garbage resulting from a bug is considered a line...
        if (!TypeOk(stmt))
        {
          throw std::runtime_error("Invalid node type left on program-level of AST in InterpretationVisitor!");
        }

        stmt->accept(*this);
      });

  return Any { };
}

Any MainInterpretationVisitor::visit(NodeFluentDecl& fluentDecl)
{
  ActionProcedureInterpretationVisitor v(DatabaseManager::getInstance().getMainDB());
  return v.visit(fluentDecl);
}

Any MainInterpretationVisitor::visit(NodeFactDecl& factDecl)
{
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
  if (!db->executeQuery(
      SQLGenerator::getInstance().getSqlStringExistsTable(
          SQLGenerator::getInstance().FACTS_TABLE_NAME_)).size())
  {
    db->executeNonQuery(SQLGenerator::getInstance().getSqlStringCreateFactsTable());
  }
  db->executeNonQuery(SQLGenerator::getInstance().getSqlStringAddFact(factDecl));

  return Any { };
}

Any MainInterpretationVisitor::visit(NodeFluentQuery& fluentQuery)
{
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
  auto formulaEvaluator = std::make_shared<FormulaEvaluator>(
      &VariableTableManager::getInstance().getMainVariableTable(),
      DatabaseManager::getInstance().getMainDB().get());

  ActionProcedureInterpretationVisitor v(formulaEvaluator,
      DatabaseManager::getInstance().getMainDB(), std::make_shared<CoutCinSignalHandler>(),
      VariableTableManager::getInstance().getMainVariableTable());

  return v.visit(idAssign);
}

Any MainInterpretationVisitor::visit(NodeSearch& nodeSearch)
{
  auto formulaEvaluator = std::make_shared<FormulaEvaluator>(
      &VariableTableManager::getInstance().getMainVariableTable(),
      DatabaseManager::getInstance().getMainDB().get());

  ActionProcedureInterpretationVisitor v(formulaEvaluator,
      DatabaseManager::getInstance().getMainDB(), std::make_shared<CoutCinSignalHandler>(),
      VariableTableManager::getInstance().getMainVariableTable());

  return v.visit(nodeSearch);
}

Any MainInterpretationVisitor::visit(NodeExogenousEventDecl& nodeExoEventDecl)
{
  ExecutableElementsContainer::getInstance().addOrReplaceExoEvent(nodeExoEventDecl);
  return Any { };
}

Any MainInterpretationVisitor::visit(NodeActionDecl& actionDecl)
{
  ExecutableElementsContainer::getInstance().addOrReplaceAction(actionDecl);
  return Any { };
}

Any MainInterpretationVisitor::visit(NodeProcDecl& procDecl)
{
  ExecutableElementsContainer::getInstance().addOrReplaceProcedure(procDecl);
  return Any { };
}

Any MainInterpretationVisitor::visit(NodeProcExecution& procExec)
{
  auto formulaEvaluator = std::make_shared<FormulaEvaluator>(
      &VariableTableManager::getInstance().getMainVariableTable(),
      DatabaseManager::getInstance().getMainDB().get());

  ActionProcedureInterpretationVisitor v(formulaEvaluator,
      DatabaseManager::getInstance().getMainDB(), std::make_shared<CoutCinSignalHandler>(),
      VariableTableManager::getInstance().getMainVariableTable());

  return Any { v.visit(procExec) };
}

Any MainInterpretationVisitor::visit(NodeSet& set)
{
  ActionProcedureInterpretationVisitor v;
  return v.visit(set);
}

Any MainInterpretationVisitor::visit(NodeTuple& tuple)
{
  ActionProcedureInterpretationVisitor v;
  return v.visit(tuple);
}

Any MainInterpretationVisitor::visit(NodeVariable& variable)
{
  ActionProcedureInterpretationVisitor apiv;
  return apiv.visit(variable);
}

Any MainInterpretationVisitor::visit(NodeVariableAssignment& varAss)
{
  ActionProcedureInterpretationVisitor apiv(
      VariableTableManager::getInstance().getMainVariableTable());
  return apiv.visit(varAss);
}

Any MainInterpretationVisitor::visit(NodeString& str)
{
  ActionProcedureInterpretationVisitor apiv;
  return apiv.visit(str);
}

Any MainInterpretationVisitor::visit(NodeSetExpression& setExpr)
{
  ActionProcedureInterpretationVisitor v;
  return v.visit(setExpr);
}

Any MainInterpretationVisitor::visit(NodeForLoop& forLoop)
{
  auto formulaEvaluator = std::make_shared<FormulaEvaluator>(
      &VariableTableManager::getInstance().getMainVariableTable(),
      DatabaseManager::getInstance().getMainDB().get());

  ActionProcedureInterpretationVisitor v(formulaEvaluator,
      DatabaseManager::getInstance().getMainDB(), std::make_shared<CoutCinSignalHandler>(),
      VariableTableManager::getInstance().getMainVariableTable());

  return v.visit(forLoop);
}

Any MainInterpretationVisitor::visit(NodeConditional& conditional)
{
  auto formulaEvaluator = std::make_shared<FormulaEvaluator>(
      &VariableTableManager::getInstance().getMainVariableTable(),
      DatabaseManager::getInstance().getMainDB().get());

  ActionProcedureInterpretationVisitor v(formulaEvaluator,
      DatabaseManager::getInstance().getMainDB(), std::make_shared<CoutCinSignalHandler>(),
      VariableTableManager::getInstance().getMainVariableTable());

  return v.visit(conditional);

}

}/* namespace execution */
} /* namespace yagi */

