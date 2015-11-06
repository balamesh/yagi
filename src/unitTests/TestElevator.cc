/**
 * @file   TestElevator.cc
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * This file is responsible for running unit tests for the elevator example.
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
 * Runs test for the elevator example.
 */
TEST(ElevatorTest, elevator)
{
  try
  {
    auto ast = yagi::unitTestHelper::tryParseFile("samples/ElevatorTest/elevator.y");
    EXPECT_TRUE(yagi::unitTestHelper::execute(ast));

    ASTBuilder::getInstance().reset();

    auto db = yagi::database::DatabaseManager::getInstance().getMainDB();

    std::string expectedFloors { "{<\"0\">, <\"1\">, <\"2\">, <\"3\">, <\"4\">, <\"5\">, <\"6\">}" };
    EXPECT_EQ(expectedFloors,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("floors"))));

    std::string expectedFon { "[EMPTY]" };
    EXPECT_EQ(expectedFon,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("fon"))));

    std::string expectedCurrFloor { "{<\"0\">}" };
    EXPECT_EQ(expectedCurrFloor,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("currFloor"))));

  }
  catch (const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    EXPECT_TRUE(false);
  }

  cleanupDatabase();
}

/**
 * Runs test for the elevator example (search1).
 */
TEST(ElevatorTest, elevatorSearch1)
{
  try
  {
    auto ast = yagi::unitTestHelper::tryParseFile("samples/ElevatorTest/elevatorSearch1.y");
    EXPECT_TRUE(yagi::unitTestHelper::execute(ast));

    ASTBuilder::getInstance().reset();

    auto db = yagi::database::DatabaseManager::getInstance().getMainDB();

    std::string expectedFloors { "{<\"0\">, <\"1\">, <\"2\">, <\"3\">, <\"4\">, <\"5\">, <\"6\">}" };
    EXPECT_EQ(expectedFloors,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("floors"))));

    std::string expectedFon { "[EMPTY]" };
    EXPECT_EQ(expectedFon,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("fon"))));

    std::string expectedCurrFloor { "{<\"0\">}" };
    EXPECT_EQ(expectedCurrFloor,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("currFloor"))));

  }
  catch (const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    EXPECT_TRUE(false);
  }

  cleanupDatabase();
}

/**
 * Runs test for the elevator example (search2).
 */
TEST(ElevatorTest, elevatorSearch2)
{
  try
  {
    auto ast = yagi::unitTestHelper::tryParseFile("samples/ElevatorTest/elevatorSearch2.y");
    EXPECT_TRUE(yagi::unitTestHelper::execute(ast));

    ASTBuilder::getInstance().reset();

    auto db = yagi::database::DatabaseManager::getInstance().getMainDB();

    std::string expectedFloors { "{<\"0\">, <\"1\">, <\"2\">, <\"3\">, <\"4\">, <\"5\">, <\"6\">}" };
    EXPECT_EQ(expectedFloors,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("floors"))));

    std::string expectedFon { "[EMPTY]" };
    EXPECT_EQ(expectedFon,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("fon"))));

    std::string expectedCurrFloor { "{<\"0\">}" };
    EXPECT_EQ(expectedCurrFloor,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("currFloor"))));

  }
  catch (const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    EXPECT_TRUE(false);
  }

  cleanupDatabase();
}

/**
 * Runs test for the elevator example (search3).
 */
TEST(ElevatorTest, elevatorSearch3)
{
  try
  {
    auto ast = yagi::unitTestHelper::tryParseFile("samples/ElevatorTest/elevatorSearch3.y");
    EXPECT_TRUE(yagi::unitTestHelper::execute(ast));

    ASTBuilder::getInstance().reset();

    auto db = yagi::database::DatabaseManager::getInstance().getMainDB();

    std::string expectedFloors { "{<\"0\">, <\"1\">, <\"2\">, <\"3\">, <\"4\">, <\"5\">, <\"6\">}" };
    EXPECT_EQ(expectedFloors,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("floors"))));

    std::string expectedFon { "[EMPTY]" };
    EXPECT_EQ(expectedFon,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("fon"))));

    std::string expectedCurrFloor { "{<\"0\">}" };
    EXPECT_EQ(expectedCurrFloor,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("currFloor"))));

  }
  catch (const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    EXPECT_TRUE(false);
  }

  cleanupDatabase();
}
