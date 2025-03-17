#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
#include <string>
#include <vector>
#include <string_view>
#include <stdexcept>


TEST_CASE("Test Error Handling 001") {

    std::string str = "hello world";
    std::cout << str << std::endl;
}

TEST_CASE("Test Error Handling 002") {
    try
    {
        // Statements that may throw exceptions you want to handle go here
        throw -1; // here's a trivial example
    }
    catch (double) // no variable name since we don't use the exception itself in the catch block below
    {
        // Any exceptions of type double thrown within the above try block get sent here
        std::cerr << "We caught an exception of type double\n";
    }
    catch (int x)
    {
        // Any exceptions of type int thrown within the above try block get sent here
        std::cerr << "We caught an int exception with value: " << x << '\n';
    }
    catch (const std::string&) // catch classes by const reference
    {
        // Any exceptions of type std::string thrown within the above try block get sent here
        std::cerr << "We caught an exception of type std::string\n";
    }

    // Execution continues here after the exception has been handled by any of the above catch blocks
    std::cout << "Continuing on our merry way\n";
}

TEST_CASE("Test Error Handling 003") {
    std::cout << "Enter a number:";
    double x;
    std::cin >> x;

    try {
        if (x < 0.0) {
            throw "Can not take sqrt of negative number";
        }

        std::cout << "The square root of " << x << " is " << std::sqrt(x) << '\n';

    } catch (const char* exception) {
        std::cout << "Caught exception: " << exception << '\n';
    }
}


/////////////////////////////////////////////////////////////

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

TEST_CASE("2 Testing Exception Case02") {
    try {
        throw my_exception2("exception2 error occurred");
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "end of test" << std::endl;
}

TEST_CASE("3 Testing Exception Case02") {
    throw my_exception2("exception2 error occurred");

    std::cout << "end of test" << std::endl;
}

