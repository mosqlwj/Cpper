# add ictest src to a static library
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS ../src/*.cpp)
add_library(ndb STATIC ${SRC})


target_include_directories(ndb 
    PUBLIC 
    ../include
    )

target_link_libraries(ndb
    PUBLIC
    json
    )
