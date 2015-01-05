/**
 * @file   DateTimeHelper.cpp
 * @author Christopher Maier
 * @date   January 2015
 *
 * Helper functions for handling date and time values.
 */

#include "DateTimeHelper.h"

namespace yagi {

std::uint64_t getNowTicks()
{
  auto time = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(time.time_since_epoch()).count();
}

const std::string currentDateTime()
{
  time_t now = time(0);
  struct tm tstruct;
  char buf[80];
  tstruct = *localtime(&now);
  // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
  // for more information about date/time format
  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

  return buf;
}

}
