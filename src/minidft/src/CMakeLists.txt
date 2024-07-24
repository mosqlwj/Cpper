#find_package(slang)

# add ictest src to a static library
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS ../src/*/*.cpp)
add_library(minidft STATIC ${SRC})



target_include_directories(minidft
    PUBLIC 
    ../include
    )

target_link_libraries(minidft
    PUBLIC
        json
#        slang::slang
    )
