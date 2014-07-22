/*
 * VariableTable.h
 *
 *  Created on: Jul 21, 2014
 *      Author: cmaier
 */

#ifndef VARIABLETABLE_H_
#define VARIABLETABLE_H_

#include <unordered_map>
#include <tuple>

namespace yagi {
namespace execution {

class VariableTable
{
  private:
    std::unordered_map<std::string, std::tuple<std::string, bool>> variables_;

  public:
    VariableTable();
    virtual ~VariableTable();

    bool variableExists(const std::string& varName) const;
    void addOrReplaceVariable(const std::string& varName, std::string value);
    void addOrReplaceVariable(const std::string& varName);
    std::string getVariableValue(const std::string& varName) const;
    bool isVariableInitialized(const std::string& varName) const;
    void setVariable(const std::string& varName, const std::string& value);
    void removeVariableIfExists(const std::string& varName);
};

} /* namespace execution */
} /* namespace yagi */

#endif /* VARIABLETABLE_H_ */
