//
// Created by liwenjie on 2024/6/27.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <cassert>

#include <iostream>
#include <vector>

using namespace std;

TEST_CASE("testing initializer_list 001") {
    // Three identical ways to initialize an int:
    int x1 = 1;
    int x2{1};
    int x3(1);

    std::vector<int> v1{1, 2, 3}; // Vector with three ints
    std::vector<int> v2 = {1, 2, 3}; // same here
    std::vector<int> v3(10, 20); // Vector with 10 ints, each have value 20

    // auto

    auto v {1}; // v is int
    //auto w {1, 2}; // error: only single elements in direct
    // auto initialization allowed! (this is new)
    auto x = {1}; // x is std::initializer_list<int>
    auto y = {1, 2}; // y is std::initializer_list<int>
    //auto z = {1, 2, 3.0}; // error: Cannot deduce element type
}