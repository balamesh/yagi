/*
 * UnitTestHelper.cpp
 *
 *  Created on: Jul 8, 2014
 *      Author: cmaier
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

ASTReturnType tryParse(const std::string& file)
{
  try
  {
    auto ast = ANTLRParser::parseYAGICodeFromFile(file);
    EXPECT_NE(ast,nullptr);

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

bool execute(ASTReturnType ast)
{
  //Invalid YAGI code...
  EXPECT_NE(ast,nullptr);

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

