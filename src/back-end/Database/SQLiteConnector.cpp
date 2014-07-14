/*
 * SQLiteConnector.cpp
 *
 *  Created on: Jul 9, 2014
 *      Author: cmaier
 */

#include "SQLiteConnector.h"

namespace yagi {
namespace database {

SQLiteConnector::~SQLiteConnector()
{

}

void SQLiteConnector::connect()
{
  int rc;

  rc = sqlite3_open(dbName_.c_str(), &pDB_);

  db_ = SQLiteDB(pDB_, [rc](sqlite3* database)
  { if (rc) sqlite3_close(database);});

  if (rc)
  {
    throw std::runtime_error(std::string("Can't open database: ") + sqlite3_errmsg(pDB_));
  }

  connected_ = true;
}

void SQLiteConnector::createTable(const NodeFluentDecl& fluentDecl)
{
  int count = fluentDecl.getDomains().size();
  createTableInternal(fluentDecl.getFluentName()->getId(), count);
}

void SQLiteConnector::createTable(const NodeFactDecl& factDecl)
{
  int count = factDecl.getDomains().size();
  createTableInternal(factDecl.getFactName()->getId(), count);
}

void SQLiteConnector::createTableInternal(const std::string& tableName, int numberOfColumns)
{
  /* Create SQL statement */
  std::string sql = "CREATE TABLE " + tableName + "(";
  char *zErrMsg = nullptr;

  SQLiteErrorMsg errorMsg = SQLiteErrorMsg(zErrMsg, [](char* ptr)
  { if (ptr) sqlite3_free(ptr);});

  for (int i = 0; i < numberOfColumns; i++)
  {
    if (i != numberOfColumns - 1)
      sql += "dom" + std::to_string(i + 1) + " TEXT,";
    else
      sql += "dom" + std::to_string(i + 1) + " TEXT);";
  }

  /* Execute SQL statement */
  int rc = sqlite3_exec(db_.get(), sql.c_str(), nullptr, 0, &zErrMsg);
  if (rc != SQLITE_OK)
  {
    throw std::runtime_error(std::string("SQL error: ") + zErrMsg);
  }
}

void SQLiteConnector::insertIntoTable(const std::string& tableName,
    const std::shared_ptr<NodeSet>& set)
{
}
void SQLiteConnector::deleteFromTable(const std::string& tableName,
    const std::shared_ptr<NodeSet>& set)
{
}

std::string SQLiteConnector::select(const std::string& tableName)
{
  return std::string { "not implemented" };
}

} //namespace end
}
