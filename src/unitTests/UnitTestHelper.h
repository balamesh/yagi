/*
 * UnitTestHelper.h
 *
 *  Created on: Jul 8, 2014
 *      Author: cmaier
 */

#ifndef UNITTESTHELPER_H_
#define UNITTESTHELPER_H_

#include "../../gtest_src/include/gtest/gtest.h"
#include "../front-end/ANTLRParser.h"

namespace yagi {

using ASTReturnType = std::shared_ptr<ASTNodeBase<>>;

namespace unitTestHelper {

ASTReturnType tryParse(const std::string& file)
{
  try
  {
    auto ast = ANTLRParser::parseYAGICodeFromFile(file);
    if (ast == nullptr)
    {
      EXPECT_TRUE(false);
      return nullptr;
    }

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

} //end namespaces
}

#endif /* UNITTESTHELPER_H_ */
