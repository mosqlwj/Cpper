cmake_minimum_required(VERSION 3.16)


# Compile as C++11
set(CMAKE_CXX_STANDARD 20)
# Require C++11 support
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# We expect external libraries to be linked statically
set(BUILD_SHARED_LIBS OFF)

project(MOSQCPP
        VERSION 1.1.0
        DESCRIPTION "My CPP Project Collection"
        LANGUAGES C CXX   # Support C & CPP language
        )

# Include guards
if (PROJECT_BINARY_DIR STREQUAL PROJECT_SOURCE_DIR)
    message(FATAL_ERROR "The binary directory of CMake cannot be the same as source directory!"
            "Please consider use 'cmake -B build' to specify a different binary directory."
            "Otherwise ZENO may fail to build, or make Git hard to exclude binary files.")
endif ()

# Default is build release
# Debug is build by cmake -B build -DCMAKE_BUILD_TYPE=Debug
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()
# print ${CMAKE_BUILD_TYPE} info
message(STATUS "PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

include(cmake/setting.cmake)
include(cmake/thirdparty.cmake)
# CMake modules
add_subdirectory(src/modern_cpp)
# add_subdirectory(src/leveldb)
add_subdirectory(thirdparty)


# Enable unit test
enable_testing()