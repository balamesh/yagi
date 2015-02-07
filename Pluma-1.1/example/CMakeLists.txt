#Based on a template provided by Karlheinz Wohlmuth <khwhth@gmail.com>.
include_directories("src/interface")
include_directories("src/plugin")
include_directories("src/host")
include_directories("../include")

set(CMAKE_BUILD_TYPE Debug)

add_library(plugin SHARED src/plugin/Connector.cpp src/plugin/Eagle.cpp src/plugin/Jaguar.cpp)
target_link_libraries(plugin pluma)

add_executable(host src/host/Main.cpp src/interface/Warrior.cpp)
target_link_libraries(host pluma)
