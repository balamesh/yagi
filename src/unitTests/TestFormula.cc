/**
 * @file   TestFormula.cc
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * This file is responsible for running unit tests for formula evaluation.
 */

#include "../../gtest_src/include/gtest/gtest.h"
#include "UnitTestHelper.h"
#include "../utils/ToStringHelper.h"
#include "../back-end/Database/DatabaseManager.h"
#include "../back-end/SQLGenerator.h"
#include "../back-end/Database/DBHelper.h"

/**
 * Runs YAGI program 'formulaExpr.y'
 */
TEST(FormulaTest, formulaAtomSetExpr1)
{
  try
  {
    auto ast = yagi::unitTestHelper::tryParse("samples/FormulaTest/formulaExpr.y");

    EXPECT_TRUE(yagi::unitTestHelper::execute(ast));

    ASTBuilder::getInstance().reset();

    auto db = yagi::database::DatabaseManager::getInstance().getMainDB();

    std::string expectedG {
        "{<\"a\">, <\"b\">, <\"c\">, <\"d\">, <\"e\">, <\"f\">, <\"g\">, <\"h\">}" };
    EXPECT_EQ(expectedG,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("f"))));
  }
  catch (const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    EXPECT_TRUE(false);
  }

  cleanupDatabase();

}

/**
 * Runs YAGI program 'formulaNegation.y'
 */
TEST(FormulaTest, formulaNegation)
{
  try
  {
    auto ast = yagi::unitTestHelper::tryParse("samples/FormulaTest/formulaNegation.y");

    EXPECT_TRUE(yagi::unitTestHelper::execute(ast));

    ASTBuilder::getInstance().reset();

    auto db = yagi::database::DatabaseManager::getInstance().getMainDB();

    std::string expectedG { "{<\"b\">, <\"f\">, <\"g\">, <\"i\">, <\"j\">}" };
    EXPECT_EQ(expectedG,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("f"))));
  }
  catch (const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    EXPECT_TRUE(false);
  }

  cleanupDatabase();

}
