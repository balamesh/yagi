/**
 * @file   CustomComparers.h
 * @author Christopher Maier
 * @date   January 2015
 *
 * Custom comparing functions for YAGI tuples.
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
