/**
 * @file   TestExoEvents.cc
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   February 2015
 *
 * This file is responsible for running unit tests for exogenous events.
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
