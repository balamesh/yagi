/**
 * @file   TestExoEvents.cc
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   February 2015
 *
 * This file is responsible for running unit tests for exogenous events.
 */

#include <iostream>
#include <fstream>
#include <thread>
using namespace std;

#include "../../gtest_src/include/gtest/gtest.h"
#include "UnitTestHelper.h"
#include "../back-end/ExecutableElementsContainer.h"
#include "../utils/ToStringHelper.h"
#include "../back-end/Database/DatabaseManager.h"
#include "../back-end/SQLGenerator.h"
#include "../back-end/Database/DBHelper.h"

/**
 * Runs test program 'exoEventTest1.y'
 */
TEST(ExoEventTest, exoEventTest)
{
  try
  {
    auto ast = yagi::unitTestHelper::tryParse("samples/ExogenousEventsTest/exoEventTest1.y");
    auto t1 = std::thread([&]()
    {
      yagi::unitTestHelper::execute(ast);
    });

    ofstream myfile;
    myfile.open("exoEventData.txt");
    myfile << "setOn;$floor;3;";
    myfile.close();

    t1.join();

    auto db = yagi::database::DatabaseManager::getInstance().getMainDB();

    std::string expectedCurrFloor { "{<\"3\">}" };

    EXPECT_EQ(expectedCurrFloor,
        yagi::fluentDBDataToString(
            db->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll("currFloor"))));

    ASTBuilder::getInstance().reset();

  }
  catch (const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    EXPECT_TRUE(false);
  }

  cleanupDatabase();
}
