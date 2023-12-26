# add ictest src to a static library
file(GLOB_RECURSE VM_SRC CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/python_vm/*.cpp)
add_library(vm STATIC ${VM_SRC})
target_include_directories(vm PUBLIC ${PROJECT_SOURCE_DIR}/src/python_vm/include/python_vm)

##########################################
# link libictest with other libs
# link spdlog
#target_link_libraries(ictest PUBLIC spdlog_header_only)
#target_include_directories(ictest PUBLIC ${PROJECT_SOURCE_DIR}/thirdparty/boost/linux/include)
#target_link_libraries(mordern-cpp PUBLIC json)
target_include_directories(vm PUBLIC ${PROJECT_SOURCE_DIR}/thirdparty/nlohmann)
target_include_directories(vm PUBLIC ${PROJECT_SOURCE_DIR}/thirdparty/doctest)
