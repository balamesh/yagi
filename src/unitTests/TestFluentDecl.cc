/*
 * TestFluentDecl.cc
 *
 *  Created on: Jul 1, 2014
 *      Author: cmaier
 */

#include "../../gtest_src/include/gtest/gtest.h"
#include "UnitTestHelper.h"
#include "../back-end/Database/DatabaseManager.h"
#include "../back-end/SQLGenerator.h"
#include "../back-end/ASTVisitors/ActionProcedureInterpretationVisitor.h"

TEST(FluentDeclTest, fluentUserDomain)
{
  try
  {
    auto ast = yagi::unitTestHelper::tryParse("src/samples/FluentDeclTest/fluentUserDomain.y");
    EXPECT_TRUE(yagi::unitTestHelper::execute(ast));

    ASTBuilder::getInstance().reset();

    auto db = yagi::database::DatabaseManager::getInstance().getMainDB();

    EXPECT_TRUE(
        db->executeQuery(SQLGenerator::getInstance().getSqlStringExistsTable("userDomain")).size()
            > 0);

    std::vector<std::string> expected1 { "r1", "r2", "r3" };
    EXPECT_EQ(expected1,
        db->executeQuery(SQLGenerator::getInstance().getSqlStringGetDomainElements("userDomain", 1)).at(
            0));

    EXPECT_TRUE(
        db->executeQuery(SQLGenerator::getInstance().getSqlStringExistsTable("threeAryFluent")).size()
            > 0);

    std::vector<std::vector<std::string>> expected2 { std::vector<std::string> { "a1", "a2" },
        std::vector<std::string> { "b1", "b2" }, std::vector<std::string> { "c1", "c2" } };

    for (int i = 1; i <= 3; i++)
    {
      EXPECT_EQ(expected2[i - 1],
          db->executeQuery(
              SQLGenerator::getInstance().getSqlStringGetDomainElements("threeAryFluent", i)).at(
              0));
    }
  }
  catch (const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    EXPECT_TRUE(false);
  }
}

TEST(FluentDeclTest, fluentStringDomain)
{
  try
  {

    auto ast = yagi::unitTestHelper::tryParse("src/samples/FluentDeclTest/fluentStringDomain.y");

    EXPECT_TRUE(yagi::unitTestHelper::execute(ast));

    ASTBuilder::getInstance().reset();

    auto db = yagi::database::DatabaseManager::getInstance().getMainDB();

    EXPECT_TRUE(
        db->executeQuery(SQLGenerator::getInstance().getSqlStringExistsTable("stringDomainFluent")).size()
            > 0);

    std::vector<std::string> expected {
        yagi::execution::ActionProcedureInterpretationVisitor::DOMAIN_STRING_ID };
    EXPECT_EQ(expected,
        db->executeQuery(
            SQLGenerator::getInstance().getSqlStringGetDomainElements("stringDomainFluent", 1)).at(
            0));
  }
  catch (const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    EXPECT_TRUE(false);
  }

}

TEST(FluentDeclTest, fluentZeroArity)
{
  auto ast = yagi::unitTestHelper::tryParse("src/samples/FluentDeclTest/fluentZeroArity.y");

  ASSERT_THROW(
  {
    throw std::runtime_error("Feature not implemented!")
    ;
  }, std::runtime_error);
}
