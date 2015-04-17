/**
 * @file   DatabaseManager.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Manages various database connection instances.
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

/**
 * Container class that manages various different database connection instances
 */
class DatabaseManager
{
  private:
    /**
     * The concrete type to use
     */
    using DataBaseConcreteType = SQLiteConnector;

    /**
     * Default ctor
     */
    DatabaseManager();

    /**
     * Default dtor
     */
    virtual ~DatabaseManager();

    /**
     * Copy ctor
     * @param Instance to copy
     */
    DatabaseManager(DatabaseManager const&);

    /**
     * Assignment operator
     * @param Instance to assign
     */
    void operator=(DatabaseManager const&);

    /**
     * Stores database connection by names
     */
    std::unordered_map<std::string, std::shared_ptr<DatabaseConnectorBase>> databases_;

    /**
     * The main database instance
     */
    std::shared_ptr<DatabaseConnectorBase> databaseMain_;

  public:
    /**
     * Singleton impl
     * @return The instance
     */
    static DatabaseManager& getInstance()
    {
      static DatabaseManager instance;
      return instance;
    }

    /**
     * Name of the main DB
     */
    const std::string MAIN_DB_NAME;

    /**
     * Returns the main DB connection
     * @return The connection to the main DB
     */
    std::shared_ptr<DatabaseConnectorBase> getMainDB();

    /**
     * Returns the connection to a specific database instance
     * @param name The name of the database instance
     * @return The connection to the db
     */
    std::shared_ptr<DatabaseConnectorBase> getDBByName(const std::string& name);

    /**
     * Clones an existing database
     * @param dbNameToClone The name of the db to clone
     * @param newDbName The name of the new (cloned) db
     * @return The connection to the new database
     */
    std::shared_ptr<DatabaseConnectorBase> getCloneWithNewName(const std::string& dbNameToClone,
        const std::string& newDbName);

    /**
     * Deletes a specific db
     * @param dbName The name of the db to delete
     */
    void deleteDB(const std::string& dbName);
};

} //end namespace
}

#endif /* DATABASEMANAGER_H_ */
