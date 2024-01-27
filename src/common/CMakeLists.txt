
# file(GLOB_RECURSE SRC CONFIGURE_DEPENDS ${HOME_COMMON}/*.cpp)
# add_library(common STATIC ${SRC})


function(cpp_test test_file)
    # get file name
    get_filename_component(test_target_name ${test_file} NAME_WE)
    add_executable(${test_target_name} ${test_file})
    target_link_libraries(${test_target_name} PUBLIC doctest)
    add_test(NAME ${test_target_name} COMMAND ${test_target_name})
endfunction(cpp_test)

cpp_test(./test_version.cpp)

# add_executable(test_version test_version.cpp)
# target_link_libraries(test_version PUBLIC doctest)



