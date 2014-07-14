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

#include "../../utils/make_unique.h"
#include "../../common/ASTNodeTypes/Declarations/FluentDecl/NodeFluentDecl.h"
#include "../../common/ASTNodeTypes/Declarations/FactDecl/NodeFactDecl.h"
#include "../../common/ASTNodeTypes/Set/NodeSet.h"

namespace yagi {
namespace database {

using SQLiteDB = std::unique_ptr<sqlite3, std::function<void(sqlite3*)>>;
using SQLiteErrorMsg = std::unique_ptr<char[], std::function<void(char*)>>;

//Based on the samples from http://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
class SQLiteConnector
{
  private:
    std::string dbName_;
    sqlite3 *pDB_;
    SQLiteDB db_;
    bool connected_;

    void connect();
    void createTableInternal(const std::string& tableName, int numberOfColumns);

  public:
    SQLiteConnector(const std::string& dbName) :
        dbName_(dbName)
    {
      connected_ = false;
      pDB_ = nullptr;
      db_ = nullptr;

      connect();
    }
    ;
    virtual ~SQLiteConnector();

    const std::string& getDbName() const
    {
      return dbName_;
    }

    bool isConnected() const
    {
      return connected_;
    }

    void createTable(const NodeFluentDecl& fluentDecl);
    void createTable(const NodeFactDecl& factDecl);
    void insertIntoTable(const std::string& tableName, const std::shared_ptr<NodeSet>& set);
    void deleteFromTable(const std::string& tableName, const std::shared_ptr<NodeSet>& set);
    std::string select(const std::string& tableName);
};

} //end namespace
}

#endif /* SQLITECONNECTOR_H_ */
