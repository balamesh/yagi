/*
 * VariableTable.h
 *
 *  Created on: Jul 21, 2014
 *      Author: cmaier
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

class VariableTable
{
  private:
    static std::string BARRIER_SYMBOL;

    std::unordered_map<std::string, std::stack<std::tuple<std::string, bool>>>variables_;
    bool showDiagnosisOutput;

    public:
    VariableTable();
    virtual ~VariableTable();

    bool variableExists(const std::string& varName) const;
    void addVariable(const std::string& varName, std::string value);
    void addVariable(const std::string& varName);
    std::string getVariableValue(const std::string& varName);
    bool isVariableInitialized(const std::string& varName) const;
    void setVariable(const std::string& varName, const std::string& value);
    void removeVariableIfExists(const std::string& varName);

    void addScope();
    void removeScope();
    VariableTable clone();
    bool isVariableInCurrentScope(const std::string& varName);

    const std::unordered_map<std::string,std::stack<std::tuple<std::string,bool> > >& getVariables() const
    {
      return variables_;
    }

    void setVariables(const std::unordered_map<std::string,std::stack<std::tuple<std::string,bool> > >& variables)
    {
      variables_ = variables;
    }
  };

}
/* namespace execution */
} /* namespace yagi */

#endif /* VARIABLETABLE_H_ */
