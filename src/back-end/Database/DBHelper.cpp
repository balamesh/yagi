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
  auto ret = db.executeQuery(SQLGenerator::getInstance().getSqlStringIsTableShadowFluent(fluentName));

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
}

}
}
