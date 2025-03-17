
############################################################
# 添加json库
add_library(json INTERFACE )
target_include_directories(json INTERFACE ${HOME_THIRDPARTY}/nlohmann)

############################################################
# 添加test库
add_library(doctest INTERFACE)
target_include_directories(doctest INTERFACE ${HOME_THIRDPARTY}/doctest)


############################################################
# 添加cli11库
add_library(cli11 INTERFACE
        ../src/modern_cpp/test_concurrent.cpp)
target_include_directories(cli11 INTERFACE ${HOME_THIRDPARTY}/cli11)

############################################################
# 添加tcl库
find_package(TCL QUIET)
if (TCL_FOUND)
    message(STATUS "TCL_INCLUDE_PATH: ${TCL_INCLUDE_PATH}")
    message(STATUS "TCL_LIBRARY: ${TCL_LIBRARY}")
else()
    message(STATUS "TCL not found")
endif()

############################################################
# 添加slang库
# add_subdirectory(${HOME_THIRDPARTY}/slang-6.0)