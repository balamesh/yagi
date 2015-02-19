#Based on a template provided by Karlheinz Wohlmuth <khwhth@gmail.com>.
project(pluma)
cmake_minimum_required(VERSION 2.6)

include_directories("include")

set(CMAKE_BUILD_TYPE DEBUG)

add_library(pluma SHARED src/Pluma/Dir.cpp src/Pluma/DLibrary.cpp src/Pluma/Host.cpp src/Pluma/PluginManager.cpp src/Pluma/Provider.cpp)
target_link_libraries(pluma dl)
add_subdirectory(example)
