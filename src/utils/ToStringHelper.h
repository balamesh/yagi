/**
 * @file   ToStringHelper.h
 * @author Christopher Maier
 * @date   January 2015
 *
 * Pretty printing helper functions that convert YAGI constructs to printable strings.
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
