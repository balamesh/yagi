/*
 * DBHelper.cpp
 *
 *  Created on: Aug 4, 2014
 *      Author: cmaier
 */
#include "DBHelper.h"

#include "../Database/DatabaseManager.h"
#include "../SQLGenerator.h"
namespace yagi {
namespace database {

bool isShadowFluent(const std::string& fluentName, const DatabaseConnectorBase& db)
{
  auto ret = db.executeQuery(
      SQLGenerator::getInstance().getSqlStringIsTableShadowFluent(fluentName));

  //select count(*) gives back exactly 1 result that's int
  return std::atoi(ret[0][0].c_str()) > 0;
}

bool isFactTable(const std::string& fluentName, const DatabaseConnectorBase& db)
{
  if (!db.executeQuery(
      SQLGenerator::getInstance().getSqlStringExistsTable(
          SQLGenerator::getInstance().FACTS_TABLE_NAME_)).size())
  {
    return false;
  }

  auto ret = db.executeQuery(SQLGenerator::getInstance().getSqlStringIsFactTable(fluentName));

  //select count(*) gives back exactly 1 result that's int
  return std::atoi(ret[0][0].c_str()) > 0;
}

void cleanupShadowFluent(const std::string& fluentName, const DatabaseConnectorBase& db)
{
  auto sqlStatements = SQLGenerator::getInstance().getSqlStringsRemoveShadowFluent(fluentName);
  for (const auto& stmt : sqlStatements)
  {
    db.executeNonQuery(stmt);
  }

  //Remove domain tables
  auto tableNames = db.executeQuery(SQLGenerator::getInstance().getSqlStringGetAllTableNames());
  for (const auto& tableName : tableNames)
  {
    if (tableName[1].find(fluentName + "_domain_dim") == 0)
    {
      db.executeNonQuery(SQLGenerator::getInstance().getSqlStringDropTable(tableName[1]));
    }
  }
}

void cleanupDatabase()
{
  auto db = DatabaseManager::getInstance().getMainDB();

  auto tableNames = db->executeQuery(SQLGenerator::getInstance().getSqlStringGetAllTableNames());
  for (const auto& tableName : tableNames)
  {
    if ((tableName[1] == SQLGenerator::getInstance().FACTS_TABLE_NAME_)
        || (tableName[1] == SQLGenerator::getInstance().SHADOW_FLUENTS_TABLE_NAME_))
    {
      db->executeNonQuery(SQLGenerator::getInstance().getSqlStringClearTable(tableName[1]));
    }

    else if (tableName[1] == "sqlite_sequence")
    {
      continue;
    }
    else
    {
      db->executeNonQuery(SQLGenerator::getInstance().getSqlStringDropTable(tableName[1]));
    }
  }

}
}
}
