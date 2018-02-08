cmake_minimum_required (VERSION 3.7.2)

set(CMAKE_COLOR_MAKEFILE   ON)

add_definitions(-DDEBUG)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fexceptions -Wall -fpermissive -ggdb")

set(HOME /home/pi)
set(ProjectsRoot ${HOME}/projects)
set(BungetRoot ${ProjectsRoot}/bunget)
set(BungetSource ${BungetRoot}/lib)
set(BungetBinary ${BungetRoot}/link)

add_subdirectory(${BungetSource} ${BungetBinary} EXCLUDE_FROM_ALL)

link_directories(${BungetRoot}/link)

add_executable (piperi main.cpp crypto.cpp callback.cpp util.cpp)
target_link_libraries (piperi bungetLib crypto++)

include_directories(${BungetSource} ${BungetSource}/include)

set(EXECUTABLE_OUTPUT_PATH ../bin)
