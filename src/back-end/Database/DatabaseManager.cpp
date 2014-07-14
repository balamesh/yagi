/*
 * DatabaseManager.cpp
 *
 *  Created on: Jul 14, 2014
 *      Author: cmaier
 */

#include "DatabaseManager.h"

namespace yagi {
namespace database {

DatabaseManager::DatabaseManager() : MAIN_DB_NAME("yagiMainDB.sqlite3")
{
  databaseMain_ = nullptr;

}

DatabaseManager::~DatabaseManager()
{
  // TODO Auto-generated destructor stub
}

} //end namespace
}
