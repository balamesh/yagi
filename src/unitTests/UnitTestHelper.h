/*
 * UnitTestHelper.h
 *
 *  Created on: Jul 8, 2014
 *      Author: cmaier
 */

#ifndef UNITTESTHELPER_H_
#define UNITTESTHELPER_H_


#include "../front-end/ANTLRParser.h"

namespace yagi {

using ASTReturnType = std::shared_ptr<ASTNodeBase<>>;

namespace unitTestHelper {

ASTReturnType tryParse(const std::string& file);
bool execute(ASTReturnType ast);


} //end namespaces
}

#endif /* UNITTESTHELPER_H_ */
