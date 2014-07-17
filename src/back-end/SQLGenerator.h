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
#include "../common/ASTNodeTypes/Expressions/NodeSetExpressionOperator.h"

class SQLGenerator
{
  private:
    SQLGenerator(SQLGenerator const&);
    void operator=(SQLGenerator const&);
    SQLGenerator();
    virtual ~SQLGenerator();

    std::string createTableInternal(const std::string& tableName, int numberOfColumns);
    std::string buildAddQuery(const std::string& tableName, std::shared_ptr<NodeTuple> tuple);
    std::string buildRemoveQuery(const std::string& tableName, std::shared_ptr<NodeTuple> tuple);
  public:
    static SQLGenerator& getInstance()
    {
      static SQLGenerator instance;
      return instance;
    }

    const std::string FACTS_TABLE_NAME_;

    std::string createTableFromFluent(const NodeFluentDecl& fluentDecl);
    std::string createTableFromFact(const NodeFactDecl& factDecl);
    std::string removeTableIfExists(const std::string& tableName);
    std::string selectAll(const std::string& tableName);
    std::string dropTable(const std::string& tableName);
    std::string existsTable(const std::string& tableName);
    std::vector<std::string> getSqlStringsForFluentSetAssign(const std::string& fluentName,
        std::shared_ptr<NodeSet> set, SetExprOperator op);
    std::string getSqlStringForTupleAssign(const std::string& fluentName,
        std::shared_ptr<NodeTuple> tuple, SetExprOperator op);
    std::string getSqlStringClearTable(const std::string& tableName);
    std::string getSqlStringIsFactTable(const std::string& tableName);
    std::string getSqlStringAddFact(const NodeFactDecl& factDecl);
    std::string getSqlStringCreateFactsTable();
    std::vector<std::string> getSqlStringsForFluentFluentAssign(const std::string& lhs,
        const std::string& rhs, SetExprOperator op, int columnCount);
    std::string getSqlStringNumberOfColumnsInTable(const std::string& tableName);

};

#endif /* SQLGENERATOR_H_ */
