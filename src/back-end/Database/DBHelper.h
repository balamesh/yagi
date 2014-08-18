/*
 * DBHelper.h
 *
 *  Created on: Aug 4, 2014
 *      Author: cmaier
 */

#ifndef DBHELPER_H_
#define DBHELPER_H_

#include <string>
#include "DatabaseConnectorBase.h"
#include "../SQLGenerator.h"

using namespace yagi::database;

namespace yagi {
namespace database {

bool isShadowFluent(const std::string& fluentName, const DatabaseConnectorBase& db);
bool isFactTable(const std::string& fluentName, const DatabaseConnectorBase& db);
void cleanupShadowFluent(const std::string& fluentName, const DatabaseConnectorBase& db);

}
}

#endif /* DBHELPER_H_ */
