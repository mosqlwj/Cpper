//
// Created by liwenjie on 2024/4/3.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"



#include <vector>
#include <string>
#include <string_view>
#include <stdexcept>

TEST_CASE("Testing Modern CPP") {
}

class my_exception : public std::runtime_error
{
public:
    using this_type     = my_exception;
    using super_type    = std::runtime_error;
public:
    my_exception(const char* msg):
                                    super_type(msg)
    {}

    my_exception() = default;
    ~my_exception() = default;
private:
    int code = 0;
};

[[noreturn]]
void raise(const char* msg)
{
    throw my_exception(msg);
    //throw runtime_error(msg);
}

TEST_CASE("Testing Exception Case01") {
    try {
        raise("error occurred");
    } catch (const std::exception& e) {
        e.what();
    }

}

////////////////////////////////////////////////////

class my_exception2 : public std::exception {

    public:
        my_exception2(const std::string& msg) : msg(msg) {}
        const char* what() const noexcept override {
            return msg.c_str();
        }
    private:
        std::string msg;
        // int code;

};

TEST_CASE("Testing Exception Case02") {
    try {
        throw my_exception2("exception2 error occurred");
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
    std::cout << "end of test" << std::endl;
}
