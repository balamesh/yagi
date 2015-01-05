/**
 * @file   TestActionDecl.cc
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * This file is responsible for running unit tests for action declarations.
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
    auto ast = yagi::unitTestHelper::tryParse("samples/ActionDeclTest/actionDeclTest.y");
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
