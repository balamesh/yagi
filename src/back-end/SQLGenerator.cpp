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
}

SQLGenerator::~SQLGenerator()
{
}

std::string SQLGenerator::getSqlStringDropTable(const std::string& tableName)
{
  return "DROP TABLE IF EXISTS " + tableName;
}

std::string SQLGenerator::getSqlStringCreateTable(const std::string& tableName, int numberOfColumns)
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

std::string SQLGenerator::getSqlStringExistsTable(const std::string& tableName)
{
  return "SELECT * FROM sqlite_master WHERE name = '" + tableName + "' AND type='table'";
}

std::vector<std::string> SQLGenerator::getSqlStringsForIDAssign(const std::string& id,
    const std::vector<std::vector<std::string>>& set, AssignmentOperator op)
{
  std::vector<std::string> sqlStrings;

  std::for_each(std::begin(set), std::end(set),
      [&sqlStrings, &id, &op, this](const std::vector<std::string>& tuple)
      {
        sqlStrings.push_back(getSqlStringForTupleAssign(id, tuple, op));

      });

  return sqlStrings;

}

//std::vector<std::string> SQLGenerator::getSqlStringsForFluentSetAssign(
//    const std::string& fluentName, std::shared_ptr<NodeSet> set, AssignmentOperator op)
//{
//  std::vector<std::string> sqlStrings;
//  auto tuples = set.get()->getTuples();
//
//  std::for_each(std::begin(tuples), std::end(tuples),
//      [&sqlStrings, &fluentName,&op, this](const std::shared_ptr<NodeTuple>& tuple)
//      {
//        sqlStrings.push_back(getSqlStringForTupleAssign(fluentName, tuple, op));
//
//      });
//
//  return sqlStrings;
//}

std::string SQLGenerator::getSqlStringForTupleAssign(const std::string& id,
    const std::vector<std::string>& tuple, AssignmentOperator op)
{
  if (op == AssignmentOperator::AddAssign || op == AssignmentOperator::Assign)
  {
    return buildAddQuery(id, tuple);

  }
  else if (op == AssignmentOperator::RemoveAssign)
  {
    return buildRemoveQuery(id, tuple);
  }
  else
    throw std::runtime_error("unknown operator in getSqlStringForTupleAssign");
}

std::string SQLGenerator::buildAddQuery(const std::string& id,
    const std::vector<std::string>& tuple)
{
  std::string sqlString = "INSERT OR IGNORE INTO " + id + " VALUES (";

  std::for_each(std::begin(tuple), std::end(tuple), [&sqlString](const std::string& val)
  {
    sqlString += val + ",";
  });

  return sqlString.substr(0, sqlString.length() - 1) + ");";
}
std::string SQLGenerator::buildRemoveQuery(const std::string& id,
    const std::vector<std::string>& tuple)
{
  std::string sqlString = "DELETE FROM " + id + " WHERE ";
  int domNr = 1;

  std::for_each(std::begin(tuple), std::end(tuple), [&sqlString,&domNr](const std::string& val)
  {
    sqlString += "dom" + std::to_string(domNr) + " = " + val + "AND ";
    domNr++;
  });

  return sqlString.substr(0, sqlString.length() - 4) + ";";
}

std::string SQLGenerator::getSqlStringSelectAll(const std::string& tableName)
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
    const std::string& rhs, AssignmentOperator op, int columnCount)
{
  std::vector<std::string> sqlStrings;

  if (op == AssignmentOperator::Assign || op == AssignmentOperator::AddAssign)
  {
    sqlStrings.push_back("INSERT OR IGNORE INTO " + lhs + " SELECT * FROM " + rhs + ";");
  }
  else if (op == AssignmentOperator::RemoveAssign) //remove everything in rhs from lhs
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
