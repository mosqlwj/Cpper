# add ictest src to a static library
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS ${HOME_MODERN_CPP}/src/*.cpp)
add_library(modern-cpp STATIC ${SRC})


target_include_directories(modern-cpp 
    PUBLIC 
    ${HOME_MODERN_CPP}/include
    )

target_link_libraries(modern-cpp 
    PUBLIC
    json
    )
