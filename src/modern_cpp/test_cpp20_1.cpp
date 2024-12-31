//
// Created by liwenjie on 2024/12/25.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>
#include <concepts>
#include <format>
#include <string>
#include <span>
#include <map>
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

TEST_CASE("Test CPP20 001")  {
    std::cout << std::format("value:{}", args(20));
}

/**
 * 测试span
 */
template <typename T>
void pspan(std::span<T> s) {
    std::cout << std::format("size: {}\n", s.size()) ;
    std::cout << std::format("size bytes: {}\n", s.size_bytes());
    for (auto& e : s) {
        e += 2; // span修改引用元素
        std::cout << std::format("{} ", e);
    }
    std::cout << std::endl;
}
TEST_CASE("Test CPP20 002")  {
    int a[] = {1, 2, 3, 4};
    pspan<int>(a);
}

/**
* 测试结构化绑定
*/

struct div_result {
    long quotient;
    long remainder;
};

div_result div(long a, long b) {
    div_result r;
    r.quotient = a / b;
    r.remainder =  a % b;
    return r;
}

std::map<std::string, int> m = {{"one", 1}, {"two", 2}, {"three", 3}};

TEST_CASE("Test CPP20 003")  {
    auto [q, r] = div(47, 5);
    std::cout << std::format("q:{}, r:{}\n", q, r);

    for (auto& [k, v] : m) {
        std::cout << std::format("key:{}, value:{}\n", k, v);
    }
}

/**
* 测试constexpr-if
*/

template <typename T>
auto get_value(const T v) {
    if constexpr(std::is_pointer_v<T>) {
        return *v;
    } else {
        return v;
    }
}

TEST_CASE("Test CPP20 004")  {
    int x{10};
    int* y{&x};
    std::cout << std::format("value:{}\n", get_value(x));
    std::cout << std::format("value:{}\n", get_value(y));
}

/**
* 测试模板函数参数推到
*/

template <typename T1, typename T2>

std::string f(const T1 a, const T2 b) {
    return std::format("{} {}", typeid(a).name(), typeid(b).name());
}

TEST_CASE("Test CPP20 005")  {
    std::cout << std::format("{}", f(1, 2));
}