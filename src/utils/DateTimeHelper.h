/**
 * @file   DateTimeHelper.h
 * @author Christopher Maier
 * @date   January 2015
 *
 * Helper functions for handling date and time values.
 */

#ifndef DATETIMEHELPER_H_
#define DATETIMEHELPER_H_

#include <string>
#include <time.h>
#include <chrono>

namespace yagi {

/**
 * Get current date/time, format is YYYY-MM-DD.HH:mm:ss
 * @return Current date/time string
 */
const std::string currentDateTime();

/**
 * Get the ticks of the current date/time
 * @return A huge value! ;-)
 */
std::uint64_t getNowTicks();

}

#endif /* DATETIMEHELPER_H_ */
