
# add uint test function
function(cpp_test test_file)
    # get file name
    get_filename_component(test_target_name ${test_file} NAME_WE)
    add_executable(${test_target_name} ${test_file})
    target_link_libraries(${test_target_name} PUBLIC doctest)
    add_test(NAME ${test_target_name} COMMAND ${test_target_name})
endfunction(cpp_test)

# test case

#cpp_test(test_modern_cpp.cpp)
#cpp_test(test_string_view.cpp)
#cpp_test(test_p_2_1.cpp)
# cpp_test(test_auto.cpp)
#cpp_test(test_object_model.cpp)
#cpp_test(test_smarter_ptr.cpp)
#cpp_test(test_exception.cpp)
#cpp_test(test_lambda.cpp)
#cpp_test(test_string.cpp)
#cpp_test(test_container.cpp)
#cpp_test(01-test_structured_bindings.cpp)
#cpp_test(10-canonical_path.cpp)
#cpp_test(10-normalize.cpp)
#cpp_test(10-grepper.cpp)
# cpp_test(10-renamer.cpp)

cpp_test(test_main.cpp)
cpp_test(test_auto.cpp)
cpp_test(test_cpp20_1.cpp)
cpp_test(test_template.cpp)
cpp_test(test_modern_cpp.cpp)
