/**
 * @file   CommandLineArgsContainer.cpp
 * @author Christopher Maier
 * @date   January 2015
 *
 * Container the stores the parameters passed via the commandline
 * to the application.
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


#include "CommandLineArgsContainer.h"

namespace yagi {
namespace container {

CommandLineArgsContainer::CommandLineArgsContainer() :
    showDebugMessages_(false), measurePerformance_(false), inputFileName_(""), outputFileName_(""), backendPlugin_("")
{

}

}
}
