/**
 * @file   FileExogenousEventProducer.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Implements exogenous events via a simple file watch approach.
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


#ifndef IFILEEXOGENOUSEVENTPRODUCER_H_
#define IFILEEXOGENOUSEVENTPRODUCER_H_

#include "../../ExogenousEvents/IExogenousEventProducer.h"
#include <chrono>

namespace yagi {
namespace execution {

/**
 * Incorporates exogenous events via watching a file for changes
 */
class FileExogenousEventProducer: public IExogenousEventProducer
{
    /**
     * The name of the file to watch
     */
    const std::string fileName = "exoEventData.txt";

    /**
     * Splits the lines in the file
     * @param lines The lines from the file
     * @return The split data from the file
     */
    std::vector<std::tuple<std::string, std::string, std::string>> splitFileLines(
        std::vector<std::string> lines);

    /**
     * Reads a textfile
     * @return The lines read
     */
    std::vector<std::string> readLinesFromFile();

    /**
     * True if file already exists, false otherwise
     */
    bool file_exists_;

    /**
     * Time point where file has been found
     */
    std::chrono::time_point<std::chrono::system_clock> time_point_file_found_;
  public:

    /**
     * Default ctor
     */
    FileExogenousEventProducer();

    /**
     * New event available?
     * @return
     */
    bool eventAvailable() override;

    /**
     * Get event + data
     * @return Event + data
     */
    std::vector<std::pair<std::string, std::unordered_map<std::string, std::string> > > getEvent()
        override;
};

} /* namespace execution */
} /* namespace yagi */

#endif /* IDEFAULTEXOGENOUSEVENTPRODUCER_H_ */
