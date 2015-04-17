/**
 * @file   SQLiteConnector.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Specific connector for SQLite databases
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

/**
 * Alias for SQLite instance and custom deleter
 */
using SQLiteDB = std::unique_ptr<sqlite3, std::function<void(sqlite3*)>>;

/**
 * Alias for SQLite error msg and custom deleter
 */
using SQLiteErrorMsg = std::unique_ptr<char[], std::function<void(char*)>>;

/**
 * Connector class for SQLite databases
 * Based on the samples from http://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
 */
class SQLiteConnector: public DatabaseConnectorBase
{
  private:

    /**
     * Cleanup db connection
     */
    void cleanup();

    /**
     * C-style db istance
     */
    sqlite3 *pDB_;

    /**
     * Wrapper for C-style instance that guarantees correct cleanup
     */
    SQLiteDB db_;

  public:

    /**
     * Ctor
     * @param dbName The name of the DB to connect to
     * @param doCleanup Cleanup connection before connecting?
     */
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

    /**
     * Ctor
     * @param dbName Name of the database
     * @param pDB C-style pointer to an existing DB
     */
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

    /**
     * Dtor
     */
    virtual ~SQLiteConnector();

    /**
     * Connects to the DB
     */
    virtual void connect() override;

    /**
     * Executes non-query SQL statement
     * @param sqlStatement The SQL statement to execute
     */
    virtual void executeNonQuery(const std::string& sqlStatement) const override;

    /**
     * Executes SQL query
     * @param selectSqlStmt The SQL query to execute
     * @return The result of the query
     */
    virtual std::vector<std::vector<std::string>> executeQuery(
        const std::string& selectSqlStmt) const override;

    /**
     * Backs up existing database (version1), taken from SQLite web page
     * @param zFilename Filename of the db
     * @param xProgress Some progress reporting callback. Not used.
     * @return 0 if ok != 0 otherwise
     */
    int backupDb(const char *zFilename, void (*xProgress)(int, int));

    /**
     * Backs up existing database (version2), taken from SQLite web page
     * Uses in-memory databases!
     * @param xProgress Some progress reporting callback.
     * @return Pointer to new database
     */
    sqlite3 *backupDb(void (*xProgress)(int, int));
};

} //end namespace
}

#endif /* SQLITECONNECTOR_H_ */
