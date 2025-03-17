//
// Created by liwenjie on 2024/5/21.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <cassert>

#include <iostream>
#include <tuple>
#include <map>
#include <stdexcept>


using namespace std;

TEST_CASE("testing Demo") {
    std::cout << "hello Demo" << std::endl;
}

bool divider_remainder(int dividend, int divisor ,int & fraction, int & remainder) {
    if (divisor == 0) {
        return false;
    }
    fraction = dividend / divisor;
    remainder = dividend % divisor;
    return true;
}

std::pair<int, int> divider_remainder(int dividend, int divisor) {
    if (divisor == 0) {
        throw std::runtime_error("divisor is zero");
    }
    return {dividend / divisor, dividend % divisor};
}