/**
 * @file   DatabaseManager.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Some database helper functions
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


#ifndef DBHELPER_H_
#define DBHELPER_H_

#include <string>
#include "DatabaseConnectorBase.h"
#include "../SQLGenerator.h"

using namespace yagi::database;

namespace yagi {
namespace database {

/**
 * Checks whether or not a fluent is a shadow fluent
 * @param fluentName The name of the fluent to check
 * @param db The database instance to check against
 * @return True if it's a shadow fluent, false otherwise
 */
bool isShadowFluent(const std::string& fluentName, const DatabaseConnectorBase& db);

/**
 * Checks whether or not a db table represents a fact
 * @param fluentName The name of the fluent/fact to check
 * @param db The database to check against
 * @return True if name corresponds to a fact, false otherwise
 */
bool isFactTable(const std::string& fluentName, const DatabaseConnectorBase& db);

/**
 * Cleans up the specific shadow fluent
 * @param fluentName The name of the shadow fluent
 * @param db The database connection
 */
void cleanupShadowFluent(const std::string& fluentName, const DatabaseConnectorBase& db);

/**
 * Cleans up the main database
 * XXX Rename function or generalize for all databases
 */
void cleanupDatabase();

}
}

#endif /* DBHELPER_H_ */
