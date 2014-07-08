/*
 * TestAssignment.cc
 *
 *  Created on: Jul 8, 2014
 *      Author: cmaier
 */
#include "../../gtest_src/include/gtest/gtest.h"
#include "UnitTestHelper.h"

TEST(AssignmentTest, assignmentSimple1)
{
  auto ast = yagi::unitTestHelper::tryParse("src/samples/AssignmentTest/assignmentSimple1.y");
  if (!ast)
    return;
  EXPECT_TRUE(true);
}

TEST(AssignmentTest, assignmentForLoop1)
{
  auto ast = yagi::unitTestHelper::tryParse("src/samples/AssignmentTest/assignmentForLoop1.y");
  if (!ast)
    return;
  EXPECT_TRUE(true);
}

TEST(AssignmentTest, assignmentConditional1)
{
  auto ast = yagi::unitTestHelper::tryParse("src/samples/AssignmentTest/assignmentConditional1.y");
  if (!ast)
    return;
  EXPECT_TRUE(true);
}
