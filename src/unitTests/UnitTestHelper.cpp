/*
 * UnitTestHelper.cpp
 *
 *  Created on: Jul 8, 2014
 *      Author: cmaier
 */
#include "UnitTestHelper.h"

namespace yagi {
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



