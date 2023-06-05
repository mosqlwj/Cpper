# add ictest src to a static library
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_library(mosq-cpp STATIC ${SRC})
target_include_directories(mosq-cpp PUBLIC ${PROJECT_SOURCE_DIR}/src/include)

##########################################
# link libictest with other libs
# link spdlog
#target_link_libraries(ictest PUBLIC spdlog_header_only)
#target_include_directories(ictest PUBLIC ${PROJECT_SOURCE_DIR}/thirdparty/boost/linux/include)
#target_link_libraries(mordern-cpp PUBLIC json)
target_include_directories(mosq-cpp PUBLIC ${PROJECT_SOURCE_DIR}/thirdparty/nlohmann)
target_include_directories(mosq-cpp PUBLIC ${PROJECT_SOURCE_DIR}/thirdparty/doctest)
