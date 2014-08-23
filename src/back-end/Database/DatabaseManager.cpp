/*
 * DatabaseManager.cpp
 *
 *  Created on: Jul 14, 2014
 *      Author: cmaier
 */

#include "DatabaseManager.h"
#include <mutex>

namespace yagi {
namespace database {

std::mutex dbManagerMutex;

DatabaseManager::DatabaseManager() :
    MAIN_DB_NAME("yagiMainDB.sqlite3")
{
  databaseMain_ = nullptr;

}

DatabaseManager::~DatabaseManager()
{

}

std::shared_ptr<DatabaseConnectorBase> DatabaseManager::getMainDB()
{
  {
    std::lock_guard<std::mutex> lk(dbManagerMutex);
    if (!databaseMain_)
    {
      databaseMain_ = std::make_shared<DataBaseConcreteType>(MAIN_DB_NAME);
    }

    return databaseMain_;
  }
}

std::shared_ptr<DatabaseConnectorBase> DatabaseManager::getDBByName(const std::string& name)
{
  {
    std::lock_guard<std::mutex> lk(dbManagerMutex);
    auto val = databases_.find(name);
    if (val == std::end(databases_))
    {
      databases_[name] = std::make_shared<DataBaseConcreteType>(name);
    }

    return databases_[name];
  }
}

void DatabaseManager::deleteDB(const std::string& dbName)
{
  {
    std::lock_guard<std::mutex> lk(dbManagerMutex);
    databases_.erase(dbName);
  }
}

std::shared_ptr<DatabaseConnectorBase> DatabaseManager::getCloneWithNewName(
    const std::string& dbNameToClone, const std::string& newDbName)
{
  {
    std::lock_guard<std::mutex> lk(dbManagerMutex);

    std::shared_ptr<SQLiteConnector> sqliteDBToClone = nullptr;

    if (dbNameToClone != MAIN_DB_NAME)
    {
      sqliteDBToClone = std::dynamic_pointer_cast<SQLiteConnector>(databases_[dbNameToClone]);
    }
    else
    {
      sqliteDBToClone = std::dynamic_pointer_cast<SQLiteConnector>(databaseMain_);
    }

    if (sqliteDBToClone->backupDb(newDbName.c_str(), nullptr) == 0)
    {
      databases_[newDbName] = std::make_shared<DataBaseConcreteType>(newDbName, false);
      return databases_[newDbName];
    }

    return nullptr;
  }
}

} //end namespace
}
