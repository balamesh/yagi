/**
 * @file   VariableTable.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Implements a variable table
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


#ifndef VARIABLETABLE_H_
#define VARIABLETABLE_H_

#include <unordered_map>
#include <stack>
#include <tuple>
#include <iostream>
#include <vector>

namespace yagi {
namespace execution {

/**
 * Class that implements a variable table
 * XXX Make VariableTable without usage of BARRIER_SYMBOL
 */
class VariableTable
{
  private:
    /**
     * The barrier symbol/canary used to implement scope
     * XXX I guess not the smartest thing to to...
     */
    static std::string BARRIER_SYMBOL;

    /**
     * Maps variable names to (possible many) values in different scopes
     */
    std::unordered_map<std::string, std::stack<std::tuple<std::string, bool>>>variables_;

    /**
     * If true, show diagnostic outputs
     */
    bool showDiagnosisOutput;

    /**
     * Current scope depth
     */
    int lvl = 0;

    /**
     * Name of the variable table
     */
    std::string name_;

    /**
     * Prefix for diagnosis output
     */
    std::string prefix_;

    public:

    /**
     * Ctor
     * @param name Name of the variable table
     */
    VariableTable(std::string name);

    /**
     * Default ctor
     */
    VariableTable();

    /**
     * Default dtor
     */
    virtual ~VariableTable();

    /**
     * Checks whether or not a variable exists
     * @param varName The name of the variable to check
     * @return True if variable exists, false otherwise
     */
    bool variableExists(const std::string& varName) const;

    /**
     * Adds variable in current scope
     * @param varName The name of the variable to add
     * @param value The value of the variable
     */
    void addVariable(const std::string& varName, std::string value);

    /**
     * Adds ariable in current scope
     * @param varName The name of the variable to add
     */
    void addVariable(const std::string& varName);

    /**
     * Gets value of variable in the current scope
     * @param varName The name of the variable
     * @return The value of the variable
     */
    std::string getVariableValue(const std::string& varName);

    /**
     * Checks whether or not a variable is initialized
     * @param varName The name of the variable to check
     * @return True if initialized, false otherwise
     */
    bool isVariableInitialized(const std::string& varName) const;

    /**
     * Set the value of a variable
     * @param varName The name of the variable
     * @param value The value to set
     */
    void setVariable(const std::string& varName, const std::string& value);

    /**
     * Remove variable from current scope in case it exists
     * @param varName The name of the variable to remove
     */
    void removeVariableIfExists(const std::string& varName);

    /**
     * Adds a new scope level
     */
    void addScope();

    /**
     * Removes one scope level
     */
    void removeScope();

    /**
     * Clones a variable table
     * @param name The name of the cloned variable table
     * @return The new variable table
     */
    VariableTable clone(const std::string& name);

    /**
     * Checks if a variable exists in the current scope
     * @param varName The name of the variable to check
     * @return True if variable exists in current scope, false otherwise
     */
    bool isVariableInCurrentScope(const std::string& varName);

    /**
     * Getter for the internal representation
     * XXX Wherever we need this, I think we shouldn't!
     * @return The internal representation of the variable table
     */
    const std::unordered_map<std::string,std::stack<std::tuple<std::string,bool> > >& getVariables() const
    {
      return variables_;
    }

    /**
     * Setter for the 'guts' variable table
     * XXX Wherever we need this, I think we shouldn't!
     * @param variables Internal representation of the variable table
     */
    void setVariables(const std::unordered_map<std::string,std::stack<std::tuple<std::string,bool> > >& variables)
    {
      variables_ = variables;
    }

    /**
     * Getter for the variable table name
     * @return The name of the variable table
     */
    const std::string& getName() const
    {
      return name_;
    }
  };

}
/* namespace execution */
} /* namespace yagi */

#endif /* VARIABLETABLE_H_ */
