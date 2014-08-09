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
    VariableTableManager();
    virtual ~VariableTableManager();
    VariableTableManager(VariableTableManager const&);
    void operator=(VariableTableManager const&);
    std::unordered_map<std::string, VariableTable> variableTables_;

  public:

    const std::string MAIN_VAR_TABLE_ID;

    static VariableTableManager& getInstance()
    {
      static VariableTableManager instance;
      return instance;
    }

    VariableTable& getVariableTable(const std::string& identifier);
    VariableTable& getMainVariableTable();
    void deleteVariableTable(const std::string& varTableName);
    VariableTable& getCloneWithNewName(const std::string& tableToClone, const std::string& newTableName);
};

} /* namespace execution */
} /* namespace yagi */

#endif /* VARIABLETABLEMANAGER_H_ */
