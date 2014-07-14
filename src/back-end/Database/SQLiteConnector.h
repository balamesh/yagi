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
#include "DatabaseConnectorBase.h"

namespace yagi {
namespace database {

using SQLiteDB = std::unique_ptr<sqlite3, std::function<void(sqlite3*)>>;
using SQLiteErrorMsg = std::unique_ptr<char[], std::function<void(char*)>>;

//Based on the samples from http://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
class SQLiteConnector : public DatabaseConnectorBase
{
  private:
    sqlite3 *pDB_;
    SQLiteDB db_;

    void connect();
    void createTableInternal(const std::string& tableName, int numberOfColumns);
    void removeTableIfExists(const std::string& tableName);
    void executeSQLNonQuery(const std::string& sqlStatement);
    std::vector<std::vector<std::string>> executeSQLQuery(const std::string& sqlQuery);

  public:
    SQLiteConnector(const std::string& dbName) :
        DatabaseConnectorBase(dbName)
    {
      pDB_ = nullptr;
      db_ = nullptr;

      connect();
    }
    ;
    virtual ~SQLiteConnector();

    void createTable(const NodeFluentDecl& fluentDecl) override;
    void createTable(const NodeFactDecl& factDecl) override;
    void insertIntoTable(const std::string& tableName, const std::shared_ptr<NodeSet>& set) override;
    void deleteFromTable(const std::string& tableName, const std::shared_ptr<NodeSet>& set) override;
    std::vector<std::vector<std::string>> select(const std::string& tableName) override;
    bool existsTable(const std::string& tableName) override;
};

} //end namespace
}

#endif /* SQLITECONNECTOR_H_ */
