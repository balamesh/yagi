/*
 * VariableTableManager.h
 *
 *  Created on: Jul 21, 2014
 *      Author: cmaier
 */

#ifndef VARIABLETABLEMANAGER_H_
#define VARIABLETABLEMANAGER_H_

#include <unordered_map>

#include "VariableTable.h"

namespace yagi {
namespace execution {

class VariableTableManager
{
  private:
    std::unordered_map<std::string, VariableTable> variableTables_;

  public:
    VariableTableManager();
    virtual ~VariableTableManager();

    VariableTable& getVariableTable(const std::string& identifier);
};

} /* namespace execution */
} /* namespace yagi */

#endif /* VARIABLETABLEMANAGER_H_ */
