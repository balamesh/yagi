/**
 * @file   UnitTestHelper.h
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * This file provides helper function for the unit test implementation.
 */

#ifndef UNITTESTHELPER_H_
#define UNITTESTHELPER_H_

#include "../front-end/ANTLRParser.h"

namespace yagi {

using ASTReturnType = std::shared_ptr<ASTNodeBase<>>;

namespace unitTestHelper {

/**
 * Tries to parse YAGI code.
 */
ASTReturnType tryParse(const std::string& file);

/**
 * Executes YAGI code and returns true if execution succeeds
 */
bool execute(ASTReturnType ast);

} //end namespaces
}

#endif /* UNITTESTHELPER_H_ */
