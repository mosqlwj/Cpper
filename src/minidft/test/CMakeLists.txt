
# add uint test function
function(cpp_test test_file)
    # get file name
    get_filename_component(test_target_name ${test_file} NAME_WE)
    add_executable(${test_target_name} ${test_file})
    target_link_libraries(${test_target_name} PUBLIC slang::slang minidft doctest)
    add_test(NAME ${test_target_name} COMMAND ${test_target_name})
endfunction(cpp_test)


function(slang_test test_file)
    # get file name
    get_filename_component(test_target_name ${test_file} NAME_WE)
    add_executable(${test_target_name} ${test_file})
    target_link_libraries(${test_target_name} PUBLIC slang::slang doctest)
    add_test(NAME ${test_target_name} COMMAND ${test_target_name})
endfunction(slang_test)


# test case

cpp_test(test_netlist.cpp)
cpp_test(test_slang.cpp)

