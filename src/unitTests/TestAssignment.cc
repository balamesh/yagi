/*
 * TestAssignment.cc
 *
 *  Created on: Jul 8, 2014
 *      Author: cmaier
 */
#include "../../gtest_src/include/gtest/gtest.h"
#include "UnitTestHelper.h"
#include "../utils/ToStringHelper.h"
#include "../back-end/Database/DatabaseManager.h"
#include "../back-end/SQLGenerator.h"
#include "../back-end/Database/DBHelper.h"

TEST(AssignmentTest, assignmentSimple1)
{
  try
  {
    auto ast = yagi::unitTestHelper::tryParse("samples/AssignmentTest/assignmentSimple1.y");
    EXPECT_TRUE(yagi::unitTestHelper::execute(ast));

    ASTBuilder::getInstance().reset();

    auto db = yagi::database::DatabaseManager::getInstance().getMainDB();

    std::string expectedF { "{<\"a\">}" };
    EXPECT_EQ(expectedF,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("f"))));

    std::string expectedG { "{<\"a\",\"x\">, <\"b\",\"y\">}" };
    EXPECT_EQ(expectedG,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("g"))));

    std::string expectedOffice {
        "{<\"p1\",\"r1\">, <\"p1\",\"r2\">, <\"p2\",\"r2\">, <\"p3\",\"r3\">}" };
    EXPECT_EQ(expectedOffice,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("office"))));

    std::string expectedF1 { "{<\"3\">}" };
    EXPECT_EQ(expectedF1,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("f1"))));

    std::string expectedF2 { "{<\"1\">, <\"2\">}" };
    EXPECT_EQ(expectedF2,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("f2"))));

  }
  catch (const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    EXPECT_TRUE(false);
  }

  cleanupDatabase();

}

TEST(AssignmentTest, assignmentForLoop1)
{
  try
  {
    auto ast = yagi::unitTestHelper::tryParse("samples/AssignmentTest/assignmentForLoop1.y");
    EXPECT_TRUE(yagi::unitTestHelper::execute(ast));

    ASTBuilder::getInstance().reset();

    auto db = yagi::database::DatabaseManager::getInstance().getMainDB();

    std::string expectedG1 { "{<\"a\",\"x\">, <\"b\",\"y\">}" };
    EXPECT_EQ(expectedG1,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("g"))));

    std::string expectedH { "{<\"a\",\"x\">, <\"b\",\"y\">}" };
    EXPECT_EQ(expectedH,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("h"))));

    std::string expectedFlu { "{<\"i\">, <\"j\">, <\"k\">}" };
    EXPECT_EQ(expectedFlu,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("flu"))));

  }
  catch (const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    EXPECT_TRUE(false);
  }

  cleanupDatabase();
}

TEST(AssignmentTest, assignmentConditional1)
{
  try
  {
    auto ast = yagi::unitTestHelper::tryParse(
        "samples/AssignmentTest/assignmentConditional1.y");
    EXPECT_TRUE(yagi::unitTestHelper::execute(ast));

    ASTBuilder::getInstance().reset();

    auto db = yagi::database::DatabaseManager::getInstance().getMainDB();

    std::string expectedG2 { "{<\"a\",\"x\">, <\"b\",\"y\">}" };
    EXPECT_EQ(expectedG2,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("g"))));

    std::string expectedH2 { "{<\"a\",\"x\">}" };
    EXPECT_EQ(expectedH2,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("h"))));

    std::string expectedFlu2 { "{<\"j\">}" };
    EXPECT_EQ(expectedFlu2,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("flu"))));

  }
  catch (const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    EXPECT_TRUE(false);
  }

  cleanupDatabase();
}

