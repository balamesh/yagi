/**
 * @file   VariableTableManager.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Manages different variable table instances, similar to DatabaseManager class
 * XXX Maybe templatize DBManager and VarTableManager to Manager<T>
 */

#ifndef VARIABLETABLEMANAGER_H_
#define VARIABLETABLEMANAGER_H_

#include <unordered_map>

#include "VariableTable.h"

namespace yagi {
namespace execution {

/**
 * Manages different variable table instances
 */
class VariableTableManager
{
  private:

    /**
     * Default ctor
     */
    VariableTableManager();

    /**
     * Default dtor
     */
    virtual ~VariableTableManager();

    /**
     * Copy ctor
     * @param Instance to copy
     */
    VariableTableManager(VariableTableManager const&);

    /**
     * Assignment operator
     * @param Instance to assign
     */
    void operator=(VariableTableManager const&);

    /**
     * Stores name-var. table tuples
     */
    std::unordered_map<std::string, VariableTable> variableTables_;

  public:

    /**
     * Name of the main variable table
     */
    const std::string MAIN_VAR_TABLE_ID;

    /**
     * Singleton impl
     * @return The instance
     */
    static VariableTableManager& getInstance()
    {
      static VariableTableManager instance;
      return instance;
    }

    /**
     * Returns specific variable table
     * @param identifier Name of the variable table
     * @return The variable table
     */
    VariableTable& getVariableTable(const std::string& identifier);

    /**
     * Getter for the main variable table
     * @return The main variable table
     */
    VariableTable& getMainVariableTable();

    /**
     * Deletes a specific variable table
     * @param varTableName The name of the variable table
     */
    void deleteVariableTable(const std::string& varTableName);

    /**
     * Clones a variable table
     * @param tableToClone The name of the variable table to clone
     * @param newTableName The name of the cloned variable table
     * @return The cloned variable table
     */
    VariableTable& getCloneWithNewName(const std::string& tableToClone,
        const std::string& newTableName);
};

} /* namespace execution */
} /* namespace yagi */

#endif /* VARIABLETABLEMANAGER_H_ */
