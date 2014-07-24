/*
 * ToStringHelper.h
 *
 *  Created on: Jul 24, 2014
 *      Author: cmaier
 */

#ifndef TOSTRINGHELPER_H_
#define TOSTRINGHELPER_H_

#include <string>
#include <vector>
#include <algorithm>

namespace yagi {

std::string fluentDBDataToString(std::vector<std::vector<std::string>> data);
std::string tupleToString(const std::vector<std::string>& tuple);
}

#endif /* TOSTRINGHELPER_H_ */
