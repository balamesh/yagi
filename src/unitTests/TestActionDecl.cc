/**
 * @file   TestActionDecl.cc
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * This file is responsible for running unit tests for action declarations.
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
#include "../back-end/ExecutableElementsContainer.h"

/**
 * Runs test program 'actionDeclTest.y'
 */
TEST(ActionDeclTest, actionDeclTest)
{
  try
  {
    auto ast = yagi::unitTestHelper::tryParseFile("samples/ActionDeclTest/actionDeclTest.y");
    EXPECT_TRUE(yagi::unitTestHelper::execute(ast));

    ASTBuilder::getInstance().reset();

    EXPECT_NE(
        yagi::execution::ExecutableElementsContainer::getInstance().getAction("testAction", 0),
        nullptr);

    EXPECT_NE(
        yagi::execution::ExecutableElementsContainer::getInstance().getAction(
            "testActionWithParams", 2), nullptr);

    EXPECT_NE(
        yagi::execution::ExecutableElementsContainer::getInstance().getAction("testSettingAction",
            2), nullptr);
  }
  catch (const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    EXPECT_TRUE(false);
  }
}
