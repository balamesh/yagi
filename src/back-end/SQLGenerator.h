/*
 * SQLGenerator.h
 *
 *  Created on: Jul 15, 2014
 *      Author: cmaier
 */

#ifndef SQLGENERATOR_H_
#define SQLGENERATOR_H_

#include <iostream>

#include "../common/ASTNodeTypes/Declarations/FluentDecl/NodeFluentDecl.h"
#include "../common/ASTNodeTypes/Declarations/FactDecl/NodeFactDecl.h"
#include "../common/ASTNodeTypes/Set/NodeSet.h"
#include "../common/ASTNodeTypes/Statements/NodeAssignmentOperator.h"

class SQLGenerator
{
  private:
    SQLGenerator(SQLGenerator const&);
    void operator=(SQLGenerator const&);
    SQLGenerator();
    virtual ~SQLGenerator();

    std::string buildAddQuery(const std::string& tableName, const std::vector<std::string>& tuple);
    std::string buildRemoveQuery(const std::string& tableName,
        const std::vector<std::string>& tuple);
  public:
    static SQLGenerator& getInstance()
    {
      static SQLGenerator instance;
      return instance;
    }

    const std::string FACTS_TABLE_NAME_;

    std::string getSqlStringCreateTable(const std::string& tableName, int numberOfColumns);
    std::string getSqlStringSelectAll(const std::string& tableName);
    std::string getSqlStringDropTable(const std::string& tableName);
    std::string getSqlStringExistsTable(const std::string& tableName);

    std::vector<std::string> getSqlStringsForIDAssign(const std::string& id,
        const std::vector<std::vector<std::string>>& set, AssignmentOperator op);

    std::string getSqlStringForTupleAssign(const std::string& id,
        const std::vector<std::string>& tuple, AssignmentOperator op);

    std::string getSqlStringClearTable(const std::string& tableName);
    std::string getSqlStringIsFactTable(const std::string& tableName);
    std::string getSqlStringAddFact(const NodeFactDecl& factDecl);
    std::string getSqlStringCreateFactsTable();
    std::vector<std::string> getSqlStringsForFluentFluentAssign(const std::string& lhs,
        const std::string& rhs, AssignmentOperator op, int columnCount);
    std::string getSqlStringNumberOfColumnsInTable(const std::string& tableName);

};

#endif /* SQLGENERATOR_H_ */
