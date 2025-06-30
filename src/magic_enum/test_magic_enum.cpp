//
// Created by liwenjie on 25-6-24.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
#include <string_view>
#include <string>
#include <magic_enum/magic_enum.hpp>

TEST_CASE("TestMagicEnum-001") {
    std::string_view str = "hello";
    std::cout << str << std::endl;
}


enum class Color { RED, GREEN, BLUE };

TEST_CASE("TestMagicEnum-002") {
    Color color = Color::BLUE;
    std::cout << magic_enum::enum_name(color) << std::endl;
}