/*
 * SQLiteConnector.cpp
 *
 *  Created on: Jul 9, 2014
 *      Author: cmaier
 */

#include "SQLiteConnector.h"

#include <fstream>
#include <mutex>

namespace yagi {
namespace database {

std::mutex dbMutex;

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

  rc = sqlite3_open(":memory:"/*dbName_.c_str()*/, &pDB_);

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
  {
    std::lock_guard<std::mutex> lk(dbMutex);

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
}

//based on http://www.codeproject.com/Tips/378808/Accessing-a-SQLite-Database-with-Cplusplus
std::vector<std::vector<std::string>> SQLiteConnector::executeQuery(
    const std::string& selectSqlStmt) const
{
  {
    std::lock_guard<std::mutex> lk(dbMutex);

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

    if (statement)
    {
      sqlite3_finalize(statement);
    }

    return data;
  }
}

/*
 ** Perform an online backup of database pDb to the database file named
 ** by zFilename. This function copies 5 database pages from pDb to
 ** zFilename, then unlocks pDb and sleeps for 250 ms, then repeats the
 ** process until the entire database is backed up.
 **
 ** The third argument passed to this function must be a pointer to a progress
 ** function. After each set of 5 pages is backed up, the progress function
 ** is invoked with two integer parameters: the number of pages left to
 ** copy, and the total number of pages in the source file. This information
 ** may be used, for example, to update a GUI progress bar.
 **
 ** While this function is running, another thread may use the database pDb, or
 ** another process may access the underlying database file via a separate
 ** connection.
 **
 ** If the backup process is successfully completed, SQLITE_OK is returned.
 ** Otherwise, if an error occurs, an SQLite error code is returned.
 */
int SQLiteConnector::backupDb(const char *zFilename, void (*xProgress)(int, int))
{
  try
  {
    std::lock_guard<std::mutex> lk(dbMutex);
    std::ifstream src(dbName_, std::ios::binary);
    std::ofstream dst(zFilename, std::ios::binary);

    dst << src.rdbuf();
    return 0;
  }
  catch (std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    return -1;
  }

//  {
//    std::lock_guard<std::mutex> lk(dbMutex);
//
//    int rc; /* Function return code */
//    sqlite3 *pFile; /* Database connection opened on zFilename */
//    sqlite3_backup *pBackup; /* Backup handle used to copy data */
//
//    /* Open the database file identified by zFilename. */
//    rc = sqlite3_open(zFilename, &pFile);
//    if (rc == SQLITE_OK)
//    {
//
//      /* Open the sqlite3_backup object used to accomplish the transfer */
//      pBackup = sqlite3_backup_init(pFile, "main", pDB_, "main");
//      if (pBackup)
//      {
//
//        /* Each iteration of this loop copies 5 database pages from database
//         ** pDb to the backup database. If the return value of backup_step()
//         ** indicates that there are still further pages to copy, sleep for
//         ** 250 ms before repeating. */
//        do
//        {
//          rc = sqlite3_backup_step(pBackup, 5);
//
//          if (xProgress)
//          {
//            xProgress(sqlite3_backup_remaining(pBackup), sqlite3_backup_pagecount(pBackup));
//          }
//
//          if (rc == SQLITE_OK || rc == SQLITE_BUSY || rc == SQLITE_LOCKED)
//          {
//            sqlite3_sleep(50);
//          }
//        }
//        while (rc == SQLITE_OK || rc == SQLITE_BUSY || rc == SQLITE_LOCKED);
//
//        /* Release resources allocated by backup_init(). */
//        (void) sqlite3_backup_finish(pBackup);
//      }
//      rc = sqlite3_errcode(pFile);
//    }
//
//    /* Close the database connection opened on database file zFilename
//     ** and return the result of this function. */
//    (void) sqlite3_close(pFile);
//    return rc;
//  }
}

sqlite3* SQLiteConnector::backupDb(void (*xProgress)(int, int))
{
  {
    std::lock_guard<std::mutex> lk(dbMutex);

    int rc; /* Function return code */
    sqlite3 *pFile = nullptr;
    sqlite3_open(":memory:"/*dbName_.c_str()*/, &pFile);

    sqlite3_backup *pBackup; /* Backup handle used to copy data */


      /* Open the sqlite3_backup object used to accomplish the transfer */
      pBackup = sqlite3_backup_init(pFile, "main", pDB_, "main");
      if (pBackup)
      {

        /* Each iteration of this loop copies 5 database pages from database
         ** pDb to the backup database. If the return value of backup_step()
         ** indicates that there are still further pages to copy, sleep for
         ** 250 ms before repeating. */
        do
        {
          rc = sqlite3_backup_step(pBackup, 5);

          if (xProgress)
          {
            xProgress(sqlite3_backup_remaining(pBackup), sqlite3_backup_pagecount(pBackup));
          }

//          if (rc == SQLITE_OK || rc == SQLITE_BUSY || rc == SQLITE_LOCKED)
//          {
//            sqlite3_sleep(20);
//          }
        }
        while (rc == SQLITE_OK || rc == SQLITE_BUSY || rc == SQLITE_LOCKED);

        /* Release resources allocated by backup_init(). */
        (void) sqlite3_backup_finish(pBackup);
      }
      rc = sqlite3_errcode(pFile);
      return pFile;
  }
}

} //namespace end
}
