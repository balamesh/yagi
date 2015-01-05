/**
 * @file   ToStringHelper.h
 * @author Christopher Maier
 * @date   January 2015
 *
 * Pretty printing helper functions that convert YAGI constructs to printable strings.
 */

#ifndef TOSTRINGHELPER_H_
#define TOSTRINGHELPER_H_

#include <string>
#include <vector>
#include <algorithm>

namespace yagi {

/**
 * Returns a "stringified" version of a YAGI set.
 */
std::string fluentDBDataToString(std::vector<std::vector<std::string>> data);

/**
 * Returns a "stringified" version of a YAGI tuple.
 * @param tuple The tuple to stringify
 * @return The string of the tuple.
 */
std::string tupleToString(const std::vector<std::string>& tuple);
}

#endif /* TOSTRINGHELPER_H_ */
