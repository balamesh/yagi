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
  cleanup();
}

void SQLiteConnector::cleanup()
{
  if (fileExists(dbName_))
  {
    if (remove(dbName_.c_str()) != 0)
    {
      std::cerr << "Can't delete database file '" << dbName_ << "'!" << std::endl;
    }
  }
}

void SQLiteConnector::connect()
{
  if (connected_)
    return;

  int rc;

  rc = sqlite3_open(dbName_.c_str(), &pDB_);
  //std::string inMemory = "file:" + dbName_ + "?mode=memory&cache=shared";
  //rc = sqlite3_open(inMemory.c_str(), &pDB_);

  db_ = SQLiteDB(pDB_, [rc](sqlite3* database)
  { if (rc) sqlite3_close(database);});

  if (rc)
  {
    throw std::runtime_error(std::string("Can't open database: ") + sqlite3_errmsg(pDB_));
  }

  //Gives a major performance improvement!
  executeNonQuery("PRAGMA synchronous = OFF;");

  connected_ = true;
}

void SQLiteConnector::executeNonQuery(const std::string& sqlStatement) const
{
  char *zErrMsg = nullptr;

  SQLiteErrorMsg errorMsg = SQLiteErrorMsg(zErrMsg, [](char* ptr)
  { if (ptr) sqlite3_free(ptr);});

  /* Execute SQL statement */
  int rc = sqlite3_exec(db_.get(), sqlStatement.c_str(), nullptr, 0, &zErrMsg);
  if (rc != SQLITE_OK)
  {
    throw std::runtime_error(std::string("SQL error: ") + zErrMsg);
  }
}

//based on http://www.codeproject.com/Tips/378808/Accessing-a-SQLite-Database-with-Cplusplus
std::vector<std::vector<std::string>> SQLiteConnector::executeQuery(
    const std::string& selectSqlStmt) const
{

  std::vector<std::vector<std::string>> data;
  sqlite3_stmt *statement;

  if (sqlite3_prepare(db_.get(), selectSqlStmt.c_str(), -1, &statement, 0) == SQLITE_OK)
  {
    int ctotal = sqlite3_column_count(statement);
    int res = 0;

    while (1)
    {
      res = sqlite3_step(statement);

      if (res == SQLITE_ROW)
      {
        std::vector<std::string> row;
        for (int i = 0; i < ctotal; i++)
        {
          auto val = sqlite3_column_text(statement, i);
          if (val != nullptr)
          {
            row.push_back((char*) val);
          }
          else
            row.push_back("<db-null>");
        }

        data.push_back(row);
      }

      if (res == SQLITE_DONE || res == SQLITE_ERROR)
      {
        break;
      }
    }
  }

  return data;
}

} //namespace end
}
