//
// Created by liwenjie on 25-6-30.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h" // For unit testing

#include <iostream>  // For standard input/output operations
#include <iomanip>   // For output formatting (std::put_time)
#include <chrono>    // For C++11 time utilities (duration, time_point, clocks)

// Use specific components from std and std::chrono to avoid broad 'using namespace'
using std::cout;
using std::endl;
using std::chrono::system_clock;
using std::chrono::time_point;
using std::chrono::duration;
using std::put_time;

// --- Custom duration and literal definition ---

// Define 'days' duration based on 'hours'
// It uses the same representation type as hours (typically long long)
// and its period is 24 times the period of an hour.
using days = duration<
    std::chrono::hours::rep,
    std::ratio_multiply<std::chrono::hours::period, std::ratio<24>>
>;

// User-defined literal operator for 'days'
// Allows writing e.g., '7_days' to represent a duration of 7 days.
// 'constexpr' ensures it can be evaluated at compile time.
constexpr days operator ""_days(unsigned long long d) {
    return days{d}; // Construct a 'days' duration object from the number 'd'
}

// --- Output operator for time_point ---

// Overload the '<<' operator to enable direct printing of system_clock time_points.
// This converts the chrono time_point to a C-style time structure for formatting.
std::ostream& operator<<(std::ostream &os, const time_point<system_clock> &t) {
    // 1. Convert chrono::time_point to std::time_t
    const auto tt = system_clock::to_time_t(t);
    // 2. Convert std::time_t to local time structure (std::tm*)
    const auto loct = std::localtime(&tt);
    // 3. Format and output using std::put_time. '%c' is a standard date and time format.
    return os << put_time(loct, "%c");
}

// --- Main program ---

TEST_CASE("CPP17-8-2")  {
    // Get the current time point from system_clock
    auto now = system_clock::now();

    // Print the current time using the overloaded '<<' operator
    cout << "当前日期和时间是：" << now << endl;

    // Define a duration of 12 hours
    std::chrono::hours chrono_12h{12};

    // Add 12 hours to the current time and print the resulting time point
    cout << "12 小时后将是：" << (now + chrono_12h) << endl;

    // Bring chrono literals (e.g., 12h, 15min) into scope
    using namespace std::chrono_literals;

    // Subtract 12 hours and 15 minutes from current time and print
    cout << "12 小时 15 分钟前是：" << (now - 12h - 15min) << endl;

    // Subtract 7 days (using our custom literal) from current time and print
    cout << "1 周前是：" << (now - 7_days) << endl;

}