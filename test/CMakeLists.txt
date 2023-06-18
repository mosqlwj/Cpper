
# include gtest(no need)
#include_directories(${PROJECT_SOURCE_DIR}/thirdparty/googletest-release-1.12.1/googletest/include)

# add uint test function
function(ictest_test test_file)
    # get file name
    get_filename_component(test_target_name ${test_file} NAME_WE)
    add_executable(${test_target_name} ${test_file})
    target_link_libraries(${test_target_name} PUBLIC mosq-cpp)
    add_test(NAME ${test_target_name} COMMAND ${test_target_name})
endfunction(ictest_test)

# test case

# ictest_test(TestDemo.cpp)
# ictest_test(TestChap01.cpp)
# ictest_test(TestJSON.cpp)
# ictest_test(TestQuikSort.cpp)
# ictest_test(TestModernCPP.cpp)
# ictest_test(TestAnimalAST.cpp)
#ictest_test(pvm/TestBufferedInputStream.cpp)
#ictest_test(pvm/TestArrayList.cpp)
#ictest_test(pvm/TestHiString.cpp)
ictest_test(pvm/TestCodeObject.cpp)
# ictest_test(modern_cpp/TestString.cpp)
# ictest_test(modern_cpp/TestConst.cpp)
# ictest_test(modern_cpp/TestCustomTypes.cpp)
# ictest_test(modern_cpp/TestDoctest.cpp)
# ictest_test(modern_cpp/TestStringView.cpp)
ictest_test(modern_cpp/Test5_5.cpp)
ictest_test(modern_cpp/Test5_6.cpp)
ictest_test(modern_cpp/Test5_8.cpp)


