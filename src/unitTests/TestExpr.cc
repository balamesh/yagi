/**
 * @file   TestExpr.cc
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * This file is responsible for running unit tests for expressions.
 */

#include "../../gtest_src/include/gtest/gtest.h"
#include "UnitTestHelper.h"
#include "../back-end/Database/DatabaseManager.h"
#include "../back-end/SQLGenerator.h"
#include "../back-end/ASTVisitors/ActionProcedureInterpretationVisitor.h"
#include "../back-end/Database/DBHelper.h"
#include "../utils/ToStringHelper.h"

/**
 * Runs YAGI program 'exprTest.y'
 */
TEST(ExprTest, exprTest)
{
  try
  {

    auto ast = yagi::unitTestHelper::tryParse("samples/ExprTest/exprTest.y");

    EXPECT_TRUE(yagi::unitTestHelper::execute(ast));

    ASTBuilder::getInstance().reset();

    auto db = yagi::database::DatabaseManager::getInstance().getMainDB();

    std::string expectedF { "{<\"a\">, <\"b\">}" };
    EXPECT_EQ(expectedF,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("f"))));

    std::string expectedF2 { "{<\"2\">}" };
    EXPECT_EQ(expectedF2,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("f2"))));

    std::string expectedF3 { "[EMPTY]" };
    EXPECT_EQ(expectedF3,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("f3"))));

    std::string expectedG { "{<\"a\",\"y\">, <\"b\",\"x\">}" };
    EXPECT_EQ(expectedG,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("g"))));

    std::string expectedAss { "{<\"p1\",\"r2\">}" };
    EXPECT_EQ(expectedAss,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("ass"))));

  }
  catch (const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    EXPECT_TRUE(false);
  }

  cleanupDatabase();

}
