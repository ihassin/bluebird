cmake_minimum_required(VERSION 3.6)

project (bluebird)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb")

set(HEADER_FILES main.h)

set(SOURCE_FILES
    main.c)

add_executable(bluebird ${SOURCE_FILES} ${HEADER_FILES})
