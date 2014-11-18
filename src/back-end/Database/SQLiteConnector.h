/*
 * SQLiteConnector.h
 *
 *  Created on: Jul 9, 2014
 *      Author: cmaier
 */

#ifndef SQLITECONNECTOR_H_
#define SQLITECONNECTOR_H_

#include <string>
#include <sqlite3.h>
#include <memory>
#include <iostream>

#include "../../utils/make_unique.h"
#include "../../utils/fileExists.h"
#include "DatabaseConnectorBase.h"

namespace yagi {
namespace database {

using SQLiteDB = std::unique_ptr<sqlite3, std::function<void(sqlite3*)>>;
using SQLiteErrorMsg = std::unique_ptr<char[], std::function<void(char*)>>;

//Based on the samples from http://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
class SQLiteConnector: public DatabaseConnectorBase
{
  private:
    void cleanup();
    sqlite3 *pDB_;
    SQLiteDB db_;

  public:
    SQLiteConnector(const std::string& dbName, bool doCleanup = true) :
        DatabaseConnectorBase(dbName)
    {
      if (doCleanup)
      {
        cleanup();
      }

      pDB_ = nullptr;
      db_ = nullptr;

      connect();
    }
    ;

    SQLiteConnector(const std::string& dbName, sqlite3 *pDB) :
        DatabaseConnectorBase(dbName)
    {
      pDB_ = pDB;

      db_ = SQLiteDB(pDB_, [](sqlite3* database)
      {
        if (database)
        {
          if (sqlite3_close(database) != SQLITE_OK)
          {
            int rc = sqlite3_errcode(database);
            std::cout << "SQLite ERROR: " << sqlite3_errstr(rc) << std::endl;
          }
        }
      });

      //Gives a major performance improvement!
      executeNonQuery("PRAGMA synchronous = OFF;");

      connected_ = true;

    }
    ;

    virtual ~SQLiteConnector();

    virtual void connect() override;
    virtual void executeNonQuery(const std::string& sqlStatement) const override;
    virtual std::vector<std::vector<std::string>> executeQuery(
        const std::string& selectSqlStmt) const override;

    int backupDb(const char *zFilename, void (*xProgress)(int, int));
    sqlite3 *backupDb(void (*xProgress)(int, int));
};

} //end namespace
}

#endif /* SQLITECONNECTOR_H_ */
