/**
 * @file   UnitTestHelper.h
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
