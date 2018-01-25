cmake_minimum_required(VERSION 3.6)
project(tests_bluebird)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb")

include_directories(../unity/src)

set(HEADER_FILES ../unity/src/unity.h unity-tests.h)

set(SOURCE_FILES
    ../unity/src/unity.c
    test.c
    main.c)

add_executable(tests_bluebird ${SOURCE_FILES} ${HEADER_FILES})

