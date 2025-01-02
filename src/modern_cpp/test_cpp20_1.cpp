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

/**
* 测试vector quick delete
*/
void printc(auto& r) {
    std::cout << std::format("1 size is {}\n", r.size());
    for (auto& e : r) {
        std::cout << std::format("{} ", e);
    }
    cout << "\n";
}

template<typename T>
void quick_delete(T& v, size_t idx) {
    if (idx < v.size()) {
        v[idx] = std::move(v.back());
        std::cout << std::format("2 size is {} \n", v.size());
        v.pop_back();
        std::cout << std::format("3 size is {} \n", v.size());
    }
}

TEST_CASE("Test CPP20 006")  {
    vector v{ 12, 196, 47, 38, 19 };
    printc(v);
    quick_delete(v, 2);
    printc(v);
}

/**
* 测试map
*/

struct BigString {
    string s_;
    BigString(const string& s) : s_(s) {
        std::cout << std::format("BigString is constructed:{}\n", s) << std::endl;
    }
};

using Mymap = std::map<std::string, BigString>;

void printm(const Mymap& m) {
    for (const auto& [k, v] : m) {
        std::cout << std::format("key:{}, value:{}\n", k, v.s_);
    }
    std::cout << "\n";
}
TEST_CASE("Test CPP20 007")  {
    Mymap m;

    m.try_emplace("Miles", "Trumpet");
    m.try_emplace("Hendrix", "Guitar");
    m.try_emplace("Krupa", "Drums");
    m.try_emplace("Zappa", "Guitar");
    m.try_emplace("Liszt", "Piano");
    printm(m);

    cout << "\n";
    cout << "emplace(Hendrix)\n";
    m.emplace("Hendrix", "Singer");
    cout << "try_emplace(Zappa)\n";
    m.try_emplace("Zappa", "Composer");
    printm(m);
}