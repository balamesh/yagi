/**
 * @file   DatabaseConnectorBase.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Basic functionality of a database connector.
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


#ifndef DATABASECONNECTORBASE_H_
#define DATABASECONNECTORBASE_H_

#include <vector>
#include <string>

namespace yagi {
namespace database {

/**
 * Abstract class that represents that basis for a database connection
 */
class DatabaseConnectorBase
{
  private:
  protected:
    /**
     * Name of the db
     */
    std::string dbName_;

    /**
     * True if connected, false otherwise
     */
    bool connected_;
  public:

    /**
     * Ctor
     * @param dbName Name of the db to connect to
     */
    DatabaseConnectorBase(const std::string& dbName) :
        dbName_(dbName)
    {
      connected_ = false;
    }
    ;

    /**
     * Default dtor
     */
    virtual ~DatabaseConnectorBase()
    {
    }
    ;

    /**
     * Getter for db name
     * @return The name of the db
     */
    const std::string& getDbName() const
    {
      return dbName_;
    }

    /**
     * Getter for db connected flag
     * @return True if connected, false otherwise
     */
    bool isConnected() const
    {
      return connected_;
    }

    /**
     * Connect to the database
     */
    virtual void connect() = 0;

    /**
     * Execute a non-query against the database
     * @param sqlStatement The SQL statement to execute
     */
    virtual void executeNonQuery(const std::string& sqlStatement) const = 0;

    /**
     * Execute a query against the database
     * @param selectSqlStmt The SQL statement to execute
     * @return The result of the query
     */
    virtual std::vector<std::vector<std::string>> executeQuery(
        const std::string& selectSqlStmt) const = 0;
};

} //end namespace
}

#endif /* DATABASECONNECTORBASE_H_ */
