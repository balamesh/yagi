/*
 * DateTimeHelper.h
 *
 *  Created on: Jul 28, 2014
 *      Author: cmaier
 */

#ifndef DATETIMEHELPER_H_
#define DATETIMEHELPER_H_

#include <string>
#include <time.h>
#include <chrono>

namespace yagi {

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime();
std::uint64_t getNowTicks();

}

#endif /* DATETIMEHELPER_H_ */
