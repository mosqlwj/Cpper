# 要求cmake版本
cmake_minimum_required(VERSION 3.16)

############################################################
# 项目设置
project(Cpper
        VERSION 0.1.0
        DESCRIPTION "My CPP Project Collection"
        LANGUAGES C CXX   # Support C & CPP language
        )

# 要求代码和生成文件不能在相同的目录
if (PROJECT_BINARY_DIR STREQUAL PROJECT_SOURCE_DIR)
    message(FATAL_ERROR "The binary directory of CMake cannot be the same as source directory!"
            "Please consider use 'cmake -B build' to specify a different binary directory."
            "Otherwise ZENO may fail to build, or make Git hard to exclude binary files.")
endif ()

############################################################
# C++支持标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 要求以静态库进行link
set(BUILD_SHARED_LIBS OFF)

############################################################
# 编译选项设置
if(BUILD_SHARED_LIBS)
    set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -fPIC")
endif()

set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
set(CMAKE_BUILD_TYPE "Debug")
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif ()


############################################################
# 设置文件输出路径
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

############################################################
# 设置路径
include(cmake/setting.cmake)
# 设置第三方库
include(cmake/thirdparty.cmake)


############################################################
# 配置版本号
configure_file(
    "${HOME_SRC}/common/config.h.in"
    "${HOME_SRC}/common/config.h"
)

############################################################
# 
add_subdirectory(./src)
add_subdirectory(thirdparty)


# Enable unit test
enable_testing()


############################################################
# 输出配置信息
message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_ARCHIVE_OUTPUT_DIRECTORY: ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
message(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
