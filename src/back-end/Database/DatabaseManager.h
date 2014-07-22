/*
 * DatabaseManager.h
 *
 *  Created on: Jul 14, 2014
 *      Author: cmaier
 */

#ifndef DATABASEMANAGER_H_
#define DATABASEMANAGER_H_

#include <memory>
#include <unordered_map>
#include <string>
#include <algorithm>

#include "DatabaseConnectorBase.h"
#include "SQLiteConnector.h"

namespace yagi {
namespace database {

class DatabaseManager
{
  private:
    using DataBaseConcreteType = SQLiteConnector;

    DatabaseManager();
    virtual ~DatabaseManager();

    DatabaseManager(DatabaseManager const&);
    void operator=(DatabaseManager const&);

    std::unordered_map<std::string, std::shared_ptr<DatabaseConnectorBase>> databases_;
    std::shared_ptr<DatabaseConnectorBase> databaseMain_;

    const std::string MAIN_DB_NAME;

  public:
    static DatabaseManager& getInstance()
    {
      static DatabaseManager instance;
      return instance;
    }

    std::shared_ptr<DatabaseConnectorBase> getMainDB()
    {
      if (!databaseMain_)
      {
        databaseMain_ = std::make_shared<DataBaseConcreteType>(MAIN_DB_NAME);
      }

      return databaseMain_;
    }

    std::shared_ptr<DatabaseConnectorBase> getDBByName(const std::string& name)
    {
      auto val = databases_.find(name);
      if (val == std::end(databases_))
      {
        databases_[name] = std::make_shared<DataBaseConcreteType>(name);
      }

      return databases_[name];
    }

};

} //end namespace
}

#endif /* DATABASEMANAGER_H_ */
