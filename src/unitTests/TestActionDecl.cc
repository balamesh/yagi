/*
 * TestActionDecl.cc
 *
 *  Created on: Jul 8, 2014
 *      Author: cmaier
 */

#include "../../gtest_src/include/gtest/gtest.h"
#include "UnitTestHelper.h"
#include "../back-end/ExecutableElementsContainer.h"

TEST(ActionDeclTest, actionDeclTest)
{
  try
  {
    auto ast = yagi::unitTestHelper::tryParse("src/samples/ActionDeclTest/actionDeclTest.y");
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
