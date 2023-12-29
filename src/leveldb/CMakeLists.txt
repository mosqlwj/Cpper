# add ictest src to a static library
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/leveldb/src/*.cpp)
add_library(leveldb STATIC ${SRC})
target_include_directories(leveldb PUBLIC ${PROJECT_SOURCE_DIR}/src/leveldb/include)

##########################################

target_include_directories(leveldb PUBLIC ${PROJECT_SOURCE_DIR}/thirdparty/nlohmann)
target_include_directories(leveldb PUBLIC ${PROJECT_SOURCE_DIR}/thirdparty/doctest)


add_subdirectory(test)