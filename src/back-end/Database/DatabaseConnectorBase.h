/*
 * IDataBaseConnection.h
 *
 *  Created on: Jul 14, 2014
 *      Author: cmaier
 */

#ifndef DATABASECONNECTORBASE_H_
#define DATABASECONNECTORBASE_H_

#include <vector>
#include <string>

namespace yagi {
namespace database {

class DatabaseConnectorBase
{
  private:
  protected:
    std::string dbName_;
    bool connected_;
  public:
    DatabaseConnectorBase(const std::string& dbName) :
        dbName_(dbName)
    {
      connected_ = false;
    }
    ;
    virtual ~DatabaseConnectorBase()
    {
    }
    ;

    const std::string& getDbName() const
    {
      return dbName_;
    }

    bool isConnected() const
    {
      return connected_;
    }

    virtual void connect() = 0;
    virtual void executeNonQuery(const std::string& sqlStatement) const = 0;
    virtual std::vector<std::vector<std::string>> executeQuery(
        const std::string& selectSqlStmt) const = 0;
};

} //end namespace
}

#endif /* DATABASECONNECTORBASE_H_ */
