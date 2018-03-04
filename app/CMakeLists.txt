cmake_minimum_required (VERSION 3.7.2)

set(CMAKE_COLOR_MAKEFILE   ON)

add_definitions(-DDEBUG)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fexceptions -Wall -fpermissive -ggdb")

set(HOME /home/pi)
set(ProjectsRoot ${HOME}/projects)

set(BungetRoot ${ProjectsRoot}/bunget)
set(BungetSource ${BungetRoot}/lib)
set(BungetBinary ${BungetRoot}/link)

set(CutestRoot ${ProjectsRoot}/cutest)
set(CutestSource ${CutestRoot}/lib)
set(CutestBinary ${CutestRoot}/link)

set(Log4cppRoot ${ProjectsRoot}/log4cpp)

add_subdirectory(${BungetSource} ${BungetBinary} EXCLUDE_FROM_ALL)
add_subdirectory(${CutestSource} ${CutestBinary} EXCLUDE_FROM_ALL)

link_directories(${BungetRoot}/link ${CutestRoot}/link)

add_executable (piperi main.cpp crypto.cpp callback.cpp util.cpp)
target_link_libraries (piperi bungetLib cutestLib crypto++ /usr/local/lib/liblog4cpp.so)

include_directories(${BungetSource} ${BungetSource}/include)
include_directories(${CutestSource} ${CutestSource}/include)


set(EXECUTABLE_OUTPUT_PATH ../bin)
