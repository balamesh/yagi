/*
 * TestFormula.cc
 *
 *  Created on: Jul 8, 2014
 *      Author: cmaier
 */
#include "../../gtest_src/include/gtest/gtest.h"
#include "UnitTestHelper.h"

TEST(FormulaTest, formulaAtomSetExpr1)
{
  auto ast = yagi::unitTestHelper::tryParse("src/samples/FormulaTest/formulaAtomSetExpr1.y");
  if (!ast)
    return;
  EXPECT_TRUE(true);
}

//TEST(FormulaTest, formulaAtomSetExpr2)
//{
//  auto ast = yagi::unitTestHelper::tryParse("src/samples/FormulaTest/formulaAtomSetExpr2.y");
//  if (!ast)
//    return;
//  EXPECT_TRUE(true);
//}

//TEST(FormulaTest, formulaAtomSetExpr3)
//{
//  auto ast = yagi::unitTestHelper::tryParse("src/samples/FormulaTest/formulaAtomSetExpr3.y");
//  if (!ast)
//    return;
//  EXPECT_TRUE(true);
//}

TEST(FormulaTest, formulaAtomValExpr1)
{
  auto ast = yagi::unitTestHelper::tryParse("src/samples/FormulaTest/formulaAtomValExpr1.y");
  if (!ast)
    return;
  EXPECT_TRUE(true);
}

TEST(FormulaTest, formulaAtomValExpr2)
{
  auto ast = yagi::unitTestHelper::tryParse("src/samples/FormulaTest/formulaAtomValExpr2.y");
  if (!ast)
    return;
  EXPECT_TRUE(true);
}

TEST(FormulaTest, formulaNegation)
{
  auto ast = yagi::unitTestHelper::tryParse("src/samples/FormulaTest/formulaNegation.y");
  if (!ast)
    return;
  EXPECT_TRUE(true);
}

TEST(FormulaTest, formulaOperatorIn1)
{
  auto ast = yagi::unitTestHelper::tryParse("src/samples/FormulaTest/formulaOperatorIn1.y");
  if (!ast)
    return;
  EXPECT_TRUE(true);
}
