/*
 * SQLGenerator.cpp
 *
 *  Created on: Jul 15, 2014
 *      Author: cmaier
 */

#include "SQLGenerator.h"

SQLGenerator::SQLGenerator() :
    FACTS_TABLE_NAME_("_facts")
{
  // TODO Auto-generated constructor stub

}

SQLGenerator::~SQLGenerator()
{
  // TODO Auto-generated destructor stub
}

std::string SQLGenerator::dropTable(const std::string& tableName)
{
  return "DROP TABLE IF EXISTS " + tableName;
}

std::string SQLGenerator::createTableFromFluent(const NodeFluentDecl& fluentDecl)
{
  int count = fluentDecl.getDomains().size();
  return createTableInternal(fluentDecl.getFluentName()->getId(), count);
}
std::string SQLGenerator::createTableFromFact(const NodeFactDecl& factDecl)
{
  int count = factDecl.getDomains().size();
  return createTableInternal(factDecl.getFactName()->getId(), count);
}

std::string SQLGenerator::existsTable(const std::string& tableName)
{
  return "SELECT * FROM sqlite_master WHERE name = '" + tableName + "' AND type='table'";
}

std::vector<std::string> SQLGenerator::getSqlStringsForFluentSetAssign(
    const std::string& fluentName, std::shared_ptr<NodeSet> set, SetExprOperator op)
{
  std::vector<std::string> sqlStrings;
  auto tuples = set.get()->getTuples();

  std::for_each(std::begin(tuples), std::end(tuples),
      [&sqlStrings, &fluentName,&op, this](const std::shared_ptr<NodeTuple>& tuple)
      {
        sqlStrings.push_back(getSqlStringForTupleAssign(fluentName, tuple, op));

      });

  return sqlStrings;
}

std::string SQLGenerator::getSqlStringForTupleAssign(const std::string& tableName,
    std::shared_ptr<NodeTuple> tuple, SetExprOperator op)
{
  if (op == SetExprOperator::AddAssign || op == SetExprOperator::Assign)
  {
    return buildAddQuery(tableName, tuple);

  }
  else if (op == SetExprOperator::RemoveAssign)
  {
    return buildRemoveQuery(tableName, tuple);
  }
  else
    throw std::runtime_error("unknown operator in getSqlStringForTupleAssign");
}

std::string SQLGenerator::buildAddQuery(const std::string& tableName,
    std::shared_ptr<NodeTuple> tuple)
{
  std::string sqlString = "INSERT OR IGNORE INTO " + tableName + " VALUES (";

  auto tupleVals = tuple->getTupleValues();
  std::for_each(std::begin(tupleVals), std::end(tupleVals),
      [&sqlString,&tupleVals](const std::shared_ptr<ASTNodeBase<>>& val)
      {
        //if it's a simple string val just take it
        auto stringVal = std::dynamic_pointer_cast<NodeString>(val);
        if (stringVal)
        {
          sqlString += stringVal->getString() + ",";
        }

        //TODO: variable?
      });

  return sqlString.substr(0, sqlString.length() - 1) + ");";
}
std::string SQLGenerator::buildRemoveQuery(const std::string& tableName,
    std::shared_ptr<NodeTuple> tuple)
{
  std::string sqlString = "DELETE FROM " + tableName + " WHERE ";
  int domNr = 1;

  auto tupleVals = tuple->getTupleValues();
  std::for_each(std::begin(tupleVals), std::end(tupleVals),
      [&sqlString,&tupleVals,&domNr](const std::shared_ptr<ASTNodeBase<>>& val)
      {
        auto stringVal = std::dynamic_pointer_cast<NodeString>(val);
        if (stringVal)
        {
          sqlString += "dom" + std::to_string(domNr) + " = " + stringVal->getString() + "AND ";
        }

        //TODO: variable?

        domNr++;
      });

  return sqlString.substr(0, sqlString.length() - 4) + ";";
}

std::string SQLGenerator::createTableInternal(const std::string& tableName, int numberOfColumns)
{
  std::string sql = "CREATE TABLE " + tableName + "(";
  std::string cols = "(";
  std::string colName = "";

  for (int i = 0; i < numberOfColumns; i++)
  {
    colName = "dom" + std::to_string(i + 1);
    sql += colName + " TEXT,";

    if (i != numberOfColumns - 1)
    {
      cols += colName + ",";
    }
    else
    {
      cols += colName + ")";
    }
  }

  sql += "UNIQUE " + cols + ");";

  return sql;
}

std::string SQLGenerator::removeTableIfExists(const std::string& tableName)
{
  return "SELECT * FROM sqlite_master WHERE name = '" + tableName + "' AND type='table'";
}
std::string SQLGenerator::selectAll(const std::string& tableName)
{
  return "SELECT * FROM " + tableName;
}

std::string SQLGenerator::getSqlStringClearTable(const std::string& tableName)
{
  return "DELETE FROM " + tableName + ";";
}

std::string SQLGenerator::getSqlStringIsFactTable(const std::string& tableName)
{
  return "SELECT COUNT FROM " + FACTS_TABLE_NAME_ + " WHERE name = '" + tableName + "';";
}

std::string SQLGenerator::getSqlStringAddFact(const NodeFactDecl& factDecl)
{
  return "INSERT INTO " + FACTS_TABLE_NAME_ + " (name) VALUES ('" + factDecl.getFactName()->getId()
      + "');";
}

std::string SQLGenerator::getSqlStringCreateFactsTable()
{
  return "CREATE TABLE " + FACTS_TABLE_NAME_
      + "(ID INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL);";
}

std::vector<std::string> SQLGenerator::getSqlStringsForFluentFluentAssign(const std::string& lhs,
    const std::string& rhs, SetExprOperator op, int columnCount)
{
  std::vector<std::string> sqlStrings;

  if (op == SetExprOperator::Assign || op == SetExprOperator::AddAssign)
  {
    sqlStrings.push_back("INSERT OR IGNORE INTO " + lhs + " SELECT * FROM " + rhs + ";");
  }
  else if (op == SetExprOperator::RemoveAssign) //remove everything in rhs from lhs
  {
    std::string sqlString = "DELETE FROM " + lhs + " WHERE EXISTS (SELECT NULL FROM " + rhs
        + " WHERE ";

    for (int columnIdx = 0; columnIdx < columnCount; columnIdx++)
    {

      sqlString += lhs + ".dom" + std::to_string(columnIdx + 1) + " = " + rhs + ".dom"
          + std::to_string(columnIdx + 1) + "AND ";
    }

    sqlStrings.push_back(sqlString.substr(0, sqlString.size() - 4) + ");");
    std::cout << sqlStrings.at(0) << std::endl;
  }
  else
    throw std::runtime_error("unknown operator in getSqlStringsForFluentFluentAssign!");

  return sqlStrings;

}

std::string SQLGenerator::getSqlStringNumberOfColumnsInTable(const std::string& tableName)
{
  return "PRAGMA table_info(" + tableName + ");";
}
