/**
 * @file   TestFactDecl.cc
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * This file is responsible for running unit tests for fact declarations.
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


#ifndef TESTFACTDECL_H_
#define TESTFACTDECL_H_

#include "../../gtest_src/include/gtest/gtest.h"
#include "UnitTestHelper.h"
#include "../back-end/Database/DBHelper.h"
#include "../back-end/Database/DatabaseManager.h"
#include "../back-end/SQLGenerator.h"
#include "../back-end/ASTVisitors/ActionProcedureInterpretationVisitor.h"

/**
 * Runs YAGI program 'factUserDomain.y'
 */
TEST(FactDeclTest, factUserDomain)
{
  try
  {
    auto ast = yagi::unitTestHelper::tryParseFile("samples/FactDeclTest/factUserDomain.y");

    EXPECT_TRUE(yagi::unitTestHelper::execute(ast));

    ASTBuilder::getInstance().reset();

    auto db = yagi::database::DatabaseManager::getInstance().getMainDB();

    EXPECT_TRUE(
        db->executeQuery(SQLGenerator::getInstance().getSqlStringExistsTable("factUserDomain")).size()
            > 0);

    EXPECT_TRUE(yagi::database::isFactTable("factUserDomain", *db.get()));

    std::vector<std::string> expected1 { "r1", "r2", "r3" };
    EXPECT_EQ(expected1,
        db->executeQuery(
            SQLGenerator::getInstance().getSqlStringGetDomainElements("factUserDomain", 1)).at(0));

    EXPECT_TRUE(
        db->executeQuery(SQLGenerator::getInstance().getSqlStringExistsTable("threeAryFact")).size()
            > 0);

    EXPECT_TRUE(yagi::database::isFactTable("threeAryFact", *db.get()));

    std::vector<std::vector<std::string>> expected2 { std::vector<std::string> { "a1", "a2" },
        std::vector<std::string> { "b1", "b2" }, std::vector<std::string> { "c1", "c2" } };

    for (int i = 1; i <= 3; i++)
    {
      EXPECT_EQ(expected2[i - 1],
          db->executeQuery(
              SQLGenerator::getInstance().getSqlStringGetDomainElements("threeAryFact", i)).at(0));
    }
  }
  catch (const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    EXPECT_TRUE(false);
  }

  cleanupDatabase();

}

/**
 * Runs YAGI program 'factStringDomain.y'
 */
TEST(FactDeclTest, factStringDomain)
{
  try
  {
    auto ast = yagi::unitTestHelper::tryParseFile("samples/FactDeclTest/factStringDomain.y");

    EXPECT_TRUE(yagi::unitTestHelper::execute(ast));

    ASTBuilder::getInstance().reset();

    auto db = yagi::database::DatabaseManager::getInstance().getMainDB();

    EXPECT_TRUE(
        db->executeQuery(SQLGenerator::getInstance().getSqlStringExistsTable("factString")).size()
            > 0);

    EXPECT_TRUE(yagi::database::isFactTable("factString", *db.get()));

    std::vector<std::string> expected {
        yagi::execution::ActionProcedureInterpretationVisitor::DOMAIN_STRING_ID };
    EXPECT_EQ(expected,
        db->executeQuery(SQLGenerator::getInstance().getSqlStringGetDomainElements("factString", 1)).at(
            0));
  }
  catch (const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    EXPECT_TRUE(false);
  }

  cleanupDatabase();
}

/**
 * Runs YAGI program 'factZeroArity.y'
 * !!This throws because the feature is not implemented yet!!
 */
TEST(FactDeclTest, factZeroArity)
{
  auto ast = yagi::unitTestHelper::tryParseFile("samples/FactDeclTest/factZeroArity.y");

  ASSERT_THROW(
  {
    throw std::runtime_error("Feature not implemented!")
    ;
  }, std::runtime_error);

  cleanupDatabase();
}

#endif /* TESTFACTDECL_H_ */
