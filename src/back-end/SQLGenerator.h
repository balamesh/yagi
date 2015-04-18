/**
 * @file   SQLGenerator.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Responsible for building SQL queries
 */

#ifndef SQLGENERATOR_H_
#define SQLGENERATOR_H_

#include <string>
#include <vector>

#include "../common/ASTNodeTypes/Statements/NodeAssignmentOperator.h"
#include "../common/ASTNodeTypes/Statements/NodeSitCalcActionExecution.h"

class NodeFactDecl;

/**
 * Generates SQL queries
 */
class SQLGenerator
{
  private:
    /**
     * Copy ctor
     * @param Instance to copy
     */
    SQLGenerator(SQLGenerator const&);

    /**
     * Assignment operator
     * @param  Instance to assign
     */
    void operator=(SQLGenerator const&);

    /**
     * Default ctor
     */
    SQLGenerator();

    /**
     * Default dtor
     */
    virtual ~SQLGenerator();

    /**
     * Builds query that adds a YAGI tuple to a database table
     * @param tableName The name of the db table
     * @param tuple The tuple to add
     * @return The SQL statement
     */
    std::string buildAddQuery(const std::string& tableName, const std::vector<std::string>& tuple);

    /**
     * Builds query that removes a YAGI tuple from a database table
     * @param tableName The name of the db table
     * @param tuple The tuple to remove
     * @return The SQL statement
     */
    std::string buildRemoveQuery(const std::string& tableName,
        const std::vector<std::string>& tuple);

    /**
     * Generates the SQL statements for building the tables that stores the domains for a fluent
     * @param tableName Name of table/fluent
     * @param domains Domains of the fluent
     * @return The SQL statements
     */
    std::vector<std::string> buildSqlStringsForDomainTables(const std::string& tableName,
        const std::vector<std::vector<std::string>>& domains);

    /**
     * If set, debug output is printed
     */
    bool printDebugOutput;
  public:

    /**
     * Singleton impl
     * @return The instance
     */
    static SQLGenerator& getInstance()
    {
      static SQLGenerator instance;
      return instance;
    }

    /**
     * Name of the the table that stores the facts
     */
    const std::string FACTS_TABLE_NAME_;

    /**
     * Name of the table that stores which fluent is a shadow fluent
     */
    const std::string SHADOW_FLUENTS_TABLE_NAME_;

    /**
     * Special column name for 0-ary fluents
     */
    const std::string ZEROARY_COLUMN_NAME;

    /**
     * Create table for a fluent and for all its domains
     * @param tableName The name of the fluent/fact
     * @param domains The domains of the fluent/fact
     * @return The SQL statements
     */
    std::vector<std::string> getSqlStringsCreateTableAndDomains(const std::string& tableName,
        const std::vector<std::vector<std::string>>& domains);

    /**
     * Store that a fluent is a shadow fluent
     * @param tableName The fluent that should be made 'shadow'
     * @return The SQL statement
     */
    std::string getSqlStringMakeTableShadowFluent(const std::string& tableName);

    /**
     * Check whether or not a fluent is a shadow fluent
     * @param tableName The fluent to check
     * @return The SQL statement
     */
    std::string getSqlStringIsTableShadowFluent(const std::string& tableName);

    /**
     * Remove fluent from the table of shadow fluents
     * @param tableName The fluent to remove
     * @return The SQL statement
     */
    std::vector<std::string> getSqlStringsRemoveShadowFluent(const std::string& tableName);

    /**
     * Get all data from a database table
     * @param tableName The table to fetch data from
     * @return The SQL statement
     */
    std::string getSqlStringSelectAll(const std::string& tableName);

    /**
     * Drop a database table
     * @param tableName The name of the table to drop
     * @return The SQL statement
     */
    std::string getSqlStringDropTable(const std::string& tableName);

    /**
     * Check whether or not a table exists
     * @param tableName The name of the table to check
     * @return The SQL statement
     */
    std::string getSqlStringExistsTable(const std::string& tableName);

    /**
     * Assign a set to a fluent/fact
     * @param id The name of the fluent/fact
     * @param set The set of tuples to assign
     * @param op The assignment operator to use
     * @return The SQL statements
     */
    std::vector<std::string> getSqlStringsForIDAssign(const std::string& id,
        const std::vector<std::vector<std::string>>& set, AssignmentOperator op);

    /**
     * Assign a tuple to a fluent/fact
     * @param id The name of the fluent/fact
     * @param tuple The tuple to assign
     * @param op The assignment operator
     * @return The SQL statement
     */
    std::string getSqlStringForTupleAssign(const std::string& id,
        const std::vector<std::string>& tuple, AssignmentOperator op);

    /**
     * Assign a tuple to a fluent/fact
     * @param id The name of the fluent/fact
     * @param tuple The tuple to assign
     * @param actionType The type of sit. calc. action (add,remove)
     * @return The SQL statement
     */
    std::string getSqlStringForTupleAssign(const std::string& id,
        const std::vector<std::string>& tuple, SitCalcActionType actionType);

    /**
     * Removes all lines from a table
     * @param tableName The table to remove from
     * @return The SQL statement
     */
    std::string getSqlStringClearTable(const std::string& tableName);

    /**
     * Checks whether or not a fluent is a fact
     * @param tableName The name of the fluent
     * @return The SQL statement
     */
    std::string getSqlStringIsFactTable(const std::string& tableName);

    /**
     * Add a fact to the database
     * @param factDecl The fact node
     * @return The SQL statement
     */
    std::string getSqlStringAddFact(const NodeFactDecl& factDecl);

    /**
     * Creates the table that stores all fluents that are facts
     * @return The SQL statement
     */
    std::string getSqlStringCreateFactsTable();

    /**
     * Creates the table that stores the shadow fluents
     * @return The SQL statement
     */
    std::string getSqlStringCreateShadowFluentsTable();

    /**
     * Assigns one fluent to another
     * @param lhs The left-hand side fluent name
     * @param rhs The right-hand side fluent name
     * @param op The assignment operator
     * @param columnCount The number of columns
     * @return The SQL statements
     */
    std::vector<std::string> getSqlStringsForFluentFluentAssign(const std::string& lhs,
        const std::string& rhs, AssignmentOperator op, int columnCount);

    /**
     * Returns the number of columns in a table
     * @param tableName The table name
     * @return The SQL statement
     */
    std::string getSqlStringNumberOfColumnsInTable(const std::string& tableName);

    /**
     * Get all table names
     * @return The SQL statement
     */
    std::string getSqlStringGetAllTableNames();

    /**
     * Get domain for a fluent in a specific dimension
     * @param fluentName The name of the fluent
     * @param dimension The dimension go get the domain values from
     * @return The SQL statement
     */
    std::string getSqlStringGetDomainElements(const std::string& fluentName, int dimension);

    /**
     * Check whether or not the domain table for a fluent already exists
     * @param fluentName The name of the fluent
     * @param dimension The dimension of the domain to check
     * @return The SQL statement
     */
    std::string getSqlStringExistsDomainTable(const std::string& fluentName, int dimension);
};

#endif /* SQLGENERATOR_H_ */
