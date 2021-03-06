/**
 * @file   DatabaseManager.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Manages various database connection instances.
 */

/*
 This file is part of YAGI.

 YAGI is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3.0 of the License, or (at your option) any later version.

 YAGI is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with YAGI.
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

//    if (sqliteDBToClone->backupDb(newDbName.c_str(), nullptr) == 0)
//    {
//      databases_[newDbName] = std::make_shared<DataBaseConcreteType>(newDbName, false);
//      return databases_[newDbName];
//    }

    auto newDB = sqliteDBToClone->backupDb(nullptr);
    databases_[newDbName] = std::make_shared<DataBaseConcreteType>(newDbName, newDB);
    return databases_[newDbName];

    return nullptr;
  }
}

} //end namespace
}
