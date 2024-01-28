# add ictest src to a static library
message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(tcl STATIC ${SRC})


target_include_directories(tcl 
    PUBLIC 
    ../include
    )

target_link_libraries(tcl 
    PUBLIC
    cli11
    )
