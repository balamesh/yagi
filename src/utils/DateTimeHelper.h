/**
 * @file   DateTimeHelper.h
 * @author Christopher Maier
 * @date   January 2015
 *
 * Helper functions for handling date and time values.
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
