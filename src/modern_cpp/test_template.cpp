//
// Created by liwenjie on 2024/12/26.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>
#include <format>
//////////////////////////////////////////
// 函数模板

template <typename T>
T max(T a, T b) {
    return a > b ? a : b;
}

struct Test {
    int v_;
    Test() = default;
    Test(int v) : v_(v) {}

    bool operator> (const Test& rhs) const {
        return v_ > rhs.v_;
    }
};
TEST_CASE("Test Func Template 001")  {
    int a{1};
    int b{2};

    std::cout << std::format("max:{}", ::max(a, b));

    Test t1{10};
    Test t2{20};
//    std::printf("max:{}", ::max(t1, t2));
    std::cout << std::format("max:{}", ::max(t1, t2).v_);
}