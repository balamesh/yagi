/**
 * @file   TestIssues.cc
 * @author Clemens Mühlbacher (cmuehlba@ist.tugraz.at)
 * @date   November 2015
 *
 * This file is responsible for running unit tests for the issue files.
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


#include "../../gtest_src/include/gtest/gtest.h"
#include "UnitTestHelper.h"
#include "../back-end/Database/DatabaseManager.h"
#include "../back-end/SQLGenerator.h"
#include "../back-end/ASTVisitors/ActionProcedureInterpretationVisitor.h"
#include "../utils/ToStringHelper.h"
#include "../back-end/Database/DBHelper.h"

/**
 * Runs test for the Issue llsf2014_prod.
 */
TEST(IssuesTest, llsf2014_prod)
{
  try
  {
    auto ast = yagi::unitTestHelper::tryParseFile("samples/Issues/llsf2014_prod.y");
    EXPECT_TRUE(yagi::unitTestHelper::execute(ast));
  }
  catch (const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    EXPECT_TRUE(false);
  }

  cleanupDatabase();
}

/*
 * Runs test for the Issue search_test_stmd.
 */
TEST(IssuesTest, search_test_stmd)
{
  try
  {
    auto ast = yagi::unitTestHelper::tryParseFile("samples/Issues/search_test_stmd.y");
    EXPECT_TRUE(yagi::unitTestHelper::execute(ast));
  }
  catch (const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    EXPECT_TRUE(false);
  }

  cleanupDatabase();
}

/*
 * Runs test for the Issue test_for_27.
 */
TEST(IssuesTest, test_for_27)
{
  try
  {
    auto ast = yagi::unitTestHelper::tryParseFile("samples/Issues/test_for_27.y");
    EXPECT_TRUE(yagi::unitTestHelper::execute(ast));
  }
  catch (const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    EXPECT_TRUE(false);
  }

  cleanupDatabase();
}

/*
 * Runs test for the Issue test_for_28.
 */
TEST(IssuesTest, test_for_28)
{
  try
  {
    auto ast = yagi::unitTestHelper::tryParseFile("samples/Issues/test_for_28.y");
    EXPECT_TRUE(yagi::unitTestHelper::execute(ast));
  }
  catch (const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    EXPECT_TRUE(false);
  }

  cleanupDatabase();
}

/*
 * Runs test for the Issue test_for_29.
 * does not terminate without exogenious events
 */
/*
TEST(IssuesTest, test_for_29)
{
  try
  {
    auto ast = yagi::unitTestHelper::tryParse("samples/Issues/test_for_29.y");
    EXPECT_TRUE(yagi::unitTestHelper::execute(ast));
  }
  catch (const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    EXPECT_TRUE(false);
  }

  cleanupDatabase();
}
 */

/*
 * Runs test for the Issue test_for_31.
 */
TEST(IssuesTest, test_for_31)
{
  try
  {
    auto ast = yagi::unitTestHelper::tryParseFile("samples/Issues/test_for_31.y");
    EXPECT_TRUE(yagi::unitTestHelper::execute(ast));
  }
  catch (const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    EXPECT_TRUE(false);
  }

  cleanupDatabase();
}

/*
 * Runs test for the Issue test_pick_while_1.
 */
TEST(IssuesTest, test_pick_while_1)
{
  try
  {
    auto ast = yagi::unitTestHelper::tryParseFile("samples/Issues/test_pick_while_1.y");
    EXPECT_TRUE(yagi::unitTestHelper::execute(ast));
  }
  catch (const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    EXPECT_TRUE(false);
  }

  cleanupDatabase();
}

/*
 * Runs test for the Issue while_2.
 */
TEST(IssuesTest, while_2)
{
  try
  {
    auto ast = yagi::unitTestHelper::tryParseFile("samples/Issues/while_2.y");
    EXPECT_TRUE(yagi::unitTestHelper::execute(ast));
  }
  catch (const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    EXPECT_TRUE(false);
  }

  cleanupDatabase();
}

/*
 * Runs test for the Issue test_exists.
 */
TEST(IssuesTest, test_exists)
{
  try
  {
    auto ast = yagi::unitTestHelper::tryParseFile("samples/Issues/test_exists.y");
    EXPECT_TRUE(yagi::unitTestHelper::execute(ast));

    ast = yagi::unitTestHelper::tryParseText("test exists <$x,$y> in at such exists <$y,$y1> in up such <$x,$y1> in fC;");
    EXPECT_TRUE(yagi::unitTestHelper::execute(ast));

    ast = yagi::unitTestHelper::tryParseText("test exists <$x,$y> in at such exists <$y,$y1> in up such not(<$x,$y1> in fC);");
    EXPECT_TRUE(yagi::unitTestHelper::execute(ast));
  }
  catch (const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    EXPECT_TRUE(false);
  }

  cleanupDatabase();
}