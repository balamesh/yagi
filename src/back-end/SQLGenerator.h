/*
 * SQLGenerator.h
 *
 *  Created on: Jul 15, 2014
 *      Author: cmaier
 */

#ifndef SQLGENERATOR_H_
#define SQLGENERATOR_H_

#include <string>
#include <vector>

#include "../common/ASTNodeTypes/Statements/NodeAssignmentOperator.h"
#include "../common/ASTNodeTypes/Statements/NodeSitCalcActionExecution.h"

class NodeFactDecl;

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
    std::vector<std::string> buildSqlStringsForDomainTables(const std::string& tableName,
        const std::vector<std::vector<std::string>>& domains);

    bool printDebugOutput;
  public:
    static SQLGenerator& getInstance()
    {
      static SQLGenerator instance;
      return instance;
    }

    const std::string FACTS_TABLE_NAME_;
    const std::string SHADOW_FLUENTS_TABLE_NAME_;

    std::vector<std::string> getSqlStringsCreateTableAndDomains(const std::string& tableName,
        const std::vector<std::vector<std::string>>& domains);
    std::string getSqlStringMakeTableShadowFluent(const std::string& tableName);
    std::string getSqlStringIsTableShadowFluent(const std::string& tableName);
    std::vector<std::string> getSqlStringsRemoveShadowFluent(const std::string& tableName);
    std::string getSqlStringSelectAll(const std::string& tableName);
    std::string getSqlStringDropTable(const std::string& tableName);
    std::string getSqlStringExistsTable(const std::string& tableName);

    std::vector<std::string> getSqlStringsForIDAssign(const std::string& id,
        const std::vector<std::vector<std::string>>& set, AssignmentOperator op);

    std::string getSqlStringForTupleAssign(const std::string& id,
        const std::vector<std::string>& tuple, AssignmentOperator op);
    std::string getSqlStringForTupleAssign(const std::string& id,
        const std::vector<std::string>& tuple, SitCalcActionType actionType);

    std::string getSqlStringClearTable(const std::string& tableName);
    std::string getSqlStringIsFactTable(const std::string& tableName);
    std::string getSqlStringAddFact(const NodeFactDecl& factDecl);
    std::string getSqlStringCreateFactsTable();
    std::string getSqlStringCreateShadowFluentsTable();
    std::vector<std::string> getSqlStringsForFluentFluentAssign(const std::string& lhs,
        const std::string& rhs, AssignmentOperator op, int columnCount);
    std::string getSqlStringNumberOfColumnsInTable(const std::string& tableName);
    std::string getSqlStringGetAllTableNames();
    std::string getSqlStringGetDomainElements(const std::string& fluentName, int dimension);
};

#endif /* SQLGENERATOR_H_ */
