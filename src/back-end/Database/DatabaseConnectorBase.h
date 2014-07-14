/*
 * IDataBaseConnection.h
 *
 *  Created on: Jul 14, 2014
 *      Author: cmaier
 */

#ifndef DATABASECONNECTORBASE_H_
#define DATABASECONNECTORBASE_H_

#include "../../common/ASTNodeTypes/Declarations/FluentDecl/NodeFluentDecl.h"
#include "../../common/ASTNodeTypes/Declarations/FactDecl/NodeFactDecl.h"
#include "../../common/ASTNodeTypes/Set/NodeSet.h"

namespace yagi {
namespace database {

class DatabaseConnectorBase
{
  private:

  protected:
    std::string dbName_;
    bool connected_;
  public:
    DatabaseConnectorBase(const std::string& dbName) : dbName_(dbName) {connected_ = false;};
    virtual ~DatabaseConnectorBase() {};

    const std::string& getDbName() const
    {
      return dbName_;
    }

    bool isConnected() const
    {
      return connected_;
    }

    virtual void createTable(const NodeFluentDecl& fluentDecl) = 0;
    virtual void createTable(const NodeFactDecl& factDecl) = 0;
    virtual void insertIntoTable(const std::string& tableName, const std::shared_ptr<NodeSet>& set) = 0;
    virtual void deleteFromTable(const std::string& tableName, const std::shared_ptr<NodeSet>& set) = 0;
    virtual std::vector<std::vector<std::string>> select(const std::string& tableName) = 0;
    virtual bool existsTable(const std::string& tableName) = 0;
};

} //end namespace
}

#endif /* DATABASECONNECTORBASE_H_ */
