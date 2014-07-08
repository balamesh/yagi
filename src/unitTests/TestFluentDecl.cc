/*
 * TestFluentDecl.cc
 *
 *  Created on: Jul 1, 2014
 *      Author: cmaier
 */
#include "../../gtest_src/include/gtest/gtest.h"
#include "UnitTestHelper.h"

TEST(FluentDeclTest, fluentUserDomain)
{
  auto ast = yagi::unitTestHelper::tryParse("src/samples/FluentDeclTest/fluentUserDomain.y");
  if (!ast)
    return;
  EXPECT_TRUE(true);
}

TEST(FluentDeclTest, fluentStringDomain)
{
  auto ast = yagi::unitTestHelper::tryParse("src/samples/FluentDeclTest/fluentStringDomain.y");
  if (!ast)
    return;
  EXPECT_TRUE(true);
}

TEST(FluentDeclTest, fluentZeroArity)
{
  auto ast = yagi::unitTestHelper::tryParse("src/samples/FluentDeclTest/fluentZeroArity.y");
  if (!ast)
    return;
  EXPECT_TRUE(true);
}
