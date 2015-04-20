/**
 * @file   CustomComparers.h
 * @author Christopher Maier
 * @date   January 2015
 *
 * Custom comparing functions for YAGI tuples.
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


#ifndef CUSTOMCOMPARERS_H_
#define CUSTOMCOMPARERS_H_

#include <vector>
#include <algorithm>

namespace yagi {
namespace comparers {

/**
 * Less than comparator for 2 YAGI tuples
 * @param v1 First tuple
 * @param v2 Second tuple
 * @return True if v1 < v2 holds, false otherwise
 */
bool tupleLessThan(const std::vector<std::string>& v1, const std::vector<std::string>& v2);

/**
 * Tests equality of 2 YAGI tuples
 * @param v1 First tuple
 * @param v2 Second tuple
 * @return True if v1 = v2 holds, false otherwise
 */
bool tuplesEqual(const std::vector<std::string>& v1, const std::vector<std::string>& v2);

}
}

#endif /* CUSTOMCOMPARERS_H_ */
