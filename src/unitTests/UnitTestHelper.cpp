/**
 * @file   UnitTestHelper.cpp
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * This file provides helper function for the unit test implementation.
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


#include "UnitTestHelper.h"

#include "../../gtest_src/include/gtest/gtest.h"
#include "../back-end/ASTVisitors/MainInterpretationVisitor.h"
#include "../back-end/ASTVisitors/RewritingVisitor.h"
#include "../front-end/astVisitors/TypeCheckVisitor.h"

using yagi::execution::MainInterpretationVisitor;
using yagi::execution::RewritingVisitor;

namespace yagi {
namespace unitTestHelper {

ASTReturnType tryParseFile(const std::string &file)
{
  try
  {
    auto ast = ANTLRParser::parseYAGICodeFromFile(file);
    EXPECT_NE(ast, nullptr);

    return ast;
  }
  catch (std::runtime_error& error)
  {
    std::cout << "[INTERNAL ERROR]: " << error.what() << std::endl;
    EXPECT_TRUE(false);
    return nullptr;
  }

  EXPECT_TRUE(false);
  return nullptr;
}

ASTReturnType tryParseText(const std::string &file)
{
  try
  {
    auto ast = ANTLRParser::parseYAGICodeFromText(file);
    EXPECT_NE(ast, nullptr);

    return ast;
  }
  catch (std::runtime_error& error)
  {
    std::cout << "[INTERNAL ERROR]: " << error.what() << std::endl;
    EXPECT_TRUE(false);
    return nullptr;
  }

  EXPECT_TRUE(false);
  return nullptr;
}

bool executeTest(ASTReturnType ast)
{
  //Invalid YAGI code...
  EXPECT_NE(ast, nullptr);

  auto prog = std::dynamic_pointer_cast<NodeProgram>(ast);
  if (!prog)
    throw std::runtime_error("AST root is no program!");

  bool result = true;

  auto stmts = prog->getProgram();
  for (const auto& stmt : stmts)
  {
    TypeCheckVisitor typeCheck;
    stmt->accept(typeCheck);

    if (typeCheck.hasTypeError())
    {
      std::string errorText = "";
      auto errors = typeCheck.getErrorTexts();
      for (const auto& error : errors)
      {
        errorText += "[ERROR] " + error + "\n";
      }

      std::cout << errorText << std::endl;
      return false;
    }

    RewritingVisitor rewriter;
    auto newStmt = stmt->accept(rewriter);

    MainInterpretationVisitor interpreter;
    auto rewrittenStmt = newStmt ? newStmt.get<std::shared_ptr<NodeForLoop>>() : nullptr;

    if (rewrittenStmt)
    {
      result = rewrittenStmt->accept(interpreter).get<bool>();
    }
    else
    {
      result = stmt->accept(interpreter).get<bool>();
    }
  }

  return result;
}

bool execute(ASTReturnType ast)
{
  //Invalid YAGI code...
  EXPECT_NE(ast, nullptr);

  auto prog = std::dynamic_pointer_cast<NodeProgram>(ast);
  if (!prog)
    throw std::runtime_error("AST root is no program!");

  auto stmts = prog->getProgram();
  for (const auto& stmt : stmts)
  {
    TypeCheckVisitor typeCheck;
    stmt->accept(typeCheck);

    if (typeCheck.hasTypeError())
    {
      std::string errorText = "";
      auto errors = typeCheck.getErrorTexts();
      for (const auto& error : errors)
      {
        errorText += "[ERROR] " + error + "\n";
      }

      std::cout << errorText << std::endl;
      return false;
    }

    RewritingVisitor rewriter;
    auto newStmt = stmt->accept(rewriter);

    MainInterpretationVisitor interpreter;
    auto rewrittenStmt = newStmt ? newStmt.get<std::shared_ptr<NodeForLoop>>() : nullptr;

    if (rewrittenStmt)
    {
      rewrittenStmt->accept(interpreter);
    }
    else
    {
      stmt->accept(interpreter);
    }
  }

  return true;
}

} //end namespaces
}

