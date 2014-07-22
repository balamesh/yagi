/*
 * CustomComparers.h
 *
 *  Created on: Jul 22, 2014
 *      Author: cmaier
 */

#ifndef CUSTOMCOMPARERS_H_
#define CUSTOMCOMPARERS_H_

#include <vector>
#include <algorithm>

namespace yagi {
namespace comparers {

bool tupleLessThan(const std::vector<std::string>& v1, const std::vector<std::string>& v2);
bool tuplesEqual(const std::vector<std::string>& v1, const std::vector<std::string>& v2);

}
}

#endif /* CUSTOMCOMPARERS_H_ */
