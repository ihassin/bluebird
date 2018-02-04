cmake_minimum_required (VERSION 3.7.2)

add_definitions(-DDEBUG)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fexceptions -Wall -fpermissive -ggdb")

link_directories(../../bunget/link)

add_executable (piperi main.cpp crypto.cpp)
target_link_libraries (piperi bungetLib crypto++)

include_directories(../../bunget/lib ../../bunget/lib/include)

set(EXECUTABLE_OUTPUT_PATH ../bin)

