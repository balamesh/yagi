/**
 * @file   SQLGenerator.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Responsible for building SQL queries
 */

#include "SQLGenerator.h"
#include "../common/ASTNodeTypes/Declarations/FactDecl/NodeFactDecl.h"
#include "../utils/CommandLineArgsContainer.h"

SQLGenerator::SQLGenerator() :
    printDebugOutput(
        yagi::container::CommandLineArgsContainer::getInstance().getShowDebugMessages()), FACTS_TABLE_NAME_(
        "_facts"), SHADOW_FLUENTS_TABLE_NAME_("_shadowFluents"), ZEROARY_COLUMN_NAME("_zeroAry")
{
}

SQLGenerator::~SQLGenerator()
{
}

std::string SQLGenerator::getSqlStringDropTable(const std::string& tableName)
{

  std::string sql = "DROP TABLE IF EXISTS " + tableName;
  if (printDebugOutput)
  {
    std::cout << sql << std::endl;
  }
  return sql;
}

std::vector<std::string> SQLGenerator::getSqlStringsRemoveShadowFluent(const std::string& tableName)
{
  //Remove table from shadow fluents table
  std::vector<std::string> sqlStrings { "DELETE FROM " + SHADOW_FLUENTS_TABLE_NAME_
      + " WHERE name = '" + tableName + "';" };

  //Delete shadow fluent table
  sqlStrings.push_back(getSqlStringDropTable(tableName));

  return sqlStrings;
}

std::string SQLGenerator::getSqlStringMakeTableShadowFluent(const std::string& tableName)
{
  return "INSERT INTO " + SHADOW_FLUENTS_TABLE_NAME_ + " (name) VALUES ('" + tableName + "');";
}

std::string SQLGenerator::getSqlStringIsTableShadowFluent(const std::string& tableName)
{
  auto ret = "SELECT COUNT(*) FROM " + SHADOW_FLUENTS_TABLE_NAME_ + " WHERE name = '" + tableName
      + "'";

  if (printDebugOutput)
  {
    std::cout << ret << std::endl;
  }

  return ret;
}

std::vector<std::string> SQLGenerator::getSqlStringsCreateTableAndDomains(
    const std::string& tableName, const std::vector<std::vector<std::string>>& domains)
{
  std::vector<std::string> sqlStrings;

  std::string sqlCreateMainTable = "CREATE TABLE " + tableName + "(";
  std::string cols = "(";
  std::string colName = "";
  int numberOfColumns = domains.size();

  for (int i = 0; i < numberOfColumns; i++)
  {
    colName = "dom" + std::to_string(i + 1);
    sqlCreateMainTable += colName + " TEXT,";

    if (i != numberOfColumns - 1)
    {
      cols += colName + ",";
    }
    else
    {
      cols += colName + ")";
    }
  }

  //CREATE TABLE f2(dom1 TEXT,UNIQUE (dom1));
  if (numberOfColumns > 0)
  {
    sqlCreateMainTable += "UNIQUE " + cols + ");";
  }
  else
  {
    sqlCreateMainTable += ZEROARY_COLUMN_NAME + " TEXT, UNIQUE (" + ZEROARY_COLUMN_NAME + "));";
    sqlStrings.push_back(sqlCreateMainTable);

    if (printDebugOutput)
    {
      for (const auto& sqlStmt : sqlStrings)
      {
        std::cout << sqlStmt << std::endl;
      }
    }

    return sqlStrings;
  }

  sqlStrings.push_back(sqlCreateMainTable);

  //Build SQL statements for creating tables that hold the domain of the fluent per dimension
  auto domainTablesStrings = buildSqlStringsForDomainTables(tableName, domains);
  sqlStrings.insert(sqlStrings.end(), domainTablesStrings.begin(), domainTablesStrings.end());

  if (printDebugOutput)
  {
    for (const auto& sqlStmt : sqlStrings)
    {
      std::cout << sqlStmt << std::endl;
    }
  }

  return sqlStrings;
}

std::vector<std::string> SQLGenerator::buildSqlStringsForDomainTables(const std::string& tableName,
    const std::vector<std::vector<std::string>>& domains)
{
  std::vector<std::string> sqlStrings;
  std::string domainTableName;

  for (size_t i = 0; i < domains.size(); i++)
  {
    domainTableName = tableName + "_domain_dim" + std::to_string(i + 1);
    std::string sql = "CREATE TABLE " + domainTableName + "(";

    for (size_t j = 0; j < domains[i].size(); j++)
    {
      auto colName = "val" + std::to_string(j + 1) + " TEXT";

      if (j != domains[i].size() - 1)
      {
        sql += colName + ",";
      }
      else
      {
        sql += colName + ")";
      }
    }

    sqlStrings.push_back(sql);

    //insert domain values
    sqlStrings.push_back(buildAddQuery(domainTableName, domains[i]));
  }

  return sqlStrings;
}

std::string SQLGenerator::getSqlStringGetDomainElements(const std::string& fluentName,
    int dimension)
{
  std::string tableName = fluentName + "_domain_dim" + std::to_string(dimension);
  return getSqlStringSelectAll(tableName);
}

std::string SQLGenerator::getSqlStringExistsDomainTable(const std::string& fluentName,
    int dimension)
{
  std::string tableName = fluentName + "_domain_dim" + std::to_string(dimension);
  return getSqlStringExistsTable(tableName);
}

std::string SQLGenerator::getSqlStringExistsTable(const std::string& tableName)
{
  return "SELECT * FROM sqlite_master WHERE name = '" + tableName + "' AND type='table'";
}

std::string SQLGenerator::getSqlStringGetAllTableNames()
{
  return "SELECT * FROM sqlite_master WHERE type='table';";
}

std::vector<std::string> SQLGenerator::getSqlStringsForIDAssign(const std::string& id,
    const std::vector<std::vector<std::string>>& set, AssignmentOperator op)
{
  std::vector<std::string> sqlStrings;

  std::for_each(std::begin(set), std::end(set),
      [&sqlStrings, &id, &op, this](const std::vector<std::string>& tuple)
      {
        auto str = getSqlStringForTupleAssign(id, tuple, op);
        sqlStrings.push_back(str);

        if (printDebugOutput)
        {
          std::cout << str << std::endl;
        }
      });

  return sqlStrings;

}

//TODO: Should not be used anymore...
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

std::string SQLGenerator::getSqlStringForTupleAssign(const std::string& id,
    const std::vector<std::string>& tuple, SitCalcActionType actionType)
{
  std::string sqlString = "";

  if (actionType == SitCalcActionType::AddAssign)
  {
    sqlString = buildAddQuery(id, tuple);

  }
  else if (actionType == SitCalcActionType::RemoveAssign)
  {
    sqlString = buildRemoveQuery(id, tuple);
  }
  else
    throw std::runtime_error("unknown operator in getSqlStringForTupleAssign");

  if (printDebugOutput)
  {
    std::cout << sqlString << std::endl;
  }

  return sqlString;
}

std::string SQLGenerator::buildAddQuery(const std::string& id,
    const std::vector<std::string>& tuple)
{
  std::string sqlString = "INSERT OR IGNORE INTO " + id + " VALUES ('";

  std::for_each(std::begin(tuple), std::end(tuple), [&sqlString](const std::string& val)
  {
    sqlString += val + "','";
  });

  return sqlString.substr(0, sqlString.length() - 2) + ");";
}
std::string SQLGenerator::buildRemoveQuery(const std::string& id,
    const std::vector<std::string>& tuple)
{
  std::string sqlString = "DELETE FROM " + id + " WHERE ";
  int domNr = 1;

  std::for_each(std::begin(tuple), std::end(tuple), [&sqlString,&domNr](const std::string& val)
  {
    sqlString += "dom" + std::to_string(domNr) + " = '" + val + "' AND ";
    domNr++;
  });

  return sqlString.substr(0, sqlString.length() - 4) + ";";
}

std::string SQLGenerator::getSqlStringSelectAll(const std::string& tableName)
{
  std::string sql = "SELECT * FROM " + tableName;

  if (printDebugOutput)
  {
    std::cout << sql << std::endl;
  }

  return sql;
}

std::string SQLGenerator::getSqlStringClearTable(const std::string& tableName)
{
  return "DELETE FROM " + tableName + ";";
}

std::string SQLGenerator::getSqlStringIsFactTable(const std::string& tableName)
{
  return "SELECT COUNT(*)  FROM " + FACTS_TABLE_NAME_ + " WHERE name = '" + tableName + "';";
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

std::string SQLGenerator::getSqlStringCreateShadowFluentsTable()
{
  return "CREATE TABLE " + SHADOW_FLUENTS_TABLE_NAME_
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

    if (printDebugOutput)
    {
      std::cout << sqlStrings.at(0) << std::endl;
    }
  }
  else
    throw std::runtime_error("unknown operator in getSqlStringsForFluentFluentAssign!");

  return sqlStrings;

}

std::string SQLGenerator::getSqlStringNumberOfColumnsInTable(const std::string& tableName)
{
  return "PRAGMA table_info(" + tableName + ");";
}
