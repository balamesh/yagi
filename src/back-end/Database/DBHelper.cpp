/*
 * DBHelper.cpp
 *
 *  Created on: Aug 4, 2014
 *      Author: cmaier
 */
#include "DBHelper.h"

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

}
}
