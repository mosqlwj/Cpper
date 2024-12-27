//
// Created by liwenjie on 2024/12/25.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>
#include <concepts>
#include <format>
#include <string>
using namespace std;
constexpr auto use_string() {
//    std::string str{"hello"};
//    return str;
    return "hello";
}


template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template <typename T>
requires Numeric<T>

T args(const T& arg) {
    return arg + 42;
}

TEST_CASE("Test Case01")  {
    std::cout << std::format("value:{}", args(20));
}