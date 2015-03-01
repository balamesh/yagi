#Based on a template provided by Karlheinz Wohlmuth <khwhth@gmail.com>.
project(pluma)
cmake_minimum_required(VERSION 2.6)

include_directories("include")

set(CMAKE_BUILD_TYPE DEBUG)

add_library(pluma src/Pluma/Dir.cpp src/Pluma/DLibrary.cpp src/Pluma/Host.cpp src/Pluma/PluginManager.cpp src/Pluma/Provider.cpp)
target_link_libraries(pluma dl)
add_subdirectory(example)

install(TARGETS pluma DESTINATION lib)
install(FILES
 include/Pluma/Connector.hpp
 include/Pluma/Pluma.hpp
 include/Pluma/Config.hpp
 include/Pluma/Provider.hpp
 include/Pluma/PluginManager.hpp
 include/Pluma/Host.hpp
 include/Pluma/Pluma.inl
 DESTINATION include/Pluma)
