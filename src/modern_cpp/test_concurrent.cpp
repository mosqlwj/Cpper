//
// Created by liwenjie on 2025/3/15.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>
#include <format>
#include <thread>

TEST_CASE("Test Concurrent 001") {

    std::cout << std::format("Hello concurrent program!") << std::endl;
}


void hello() {
    std::cout << "hello world!" << std::endl;
}

TEST_CASE("Test Concurrent 002") {
    std::thread t{hello};
    t.join();
}

TEST_CASE("Test Concurrent 003") {
    auto n = std::thread::hardware_concurrency();
    std::cout << std::format("hardware_concurrency: {}", n) << std::endl;
}

TEST_CASE("Test Concurrent 004") {
    std::thread t{[]() { std::cout << "Test Concurrent 004" << std::endl; }};
    t.join();
}

// 函数对象

struct func{
    int& m_i;
    func(int& i) : m_i{i} {}

    void operator()(int n) const {
        for (auto j = 0; j <= n; ++j) {
            m_i += j;
        }
    }
};

TEST_CASE("Test Concurrent 005") {
    int n = 0;
    std::thread t{func{n}, 100};
    t.join();
    std::cout << std::format("n: {}", n) << std::endl;
    // CHECK(n == 5050);
}


// RAII

void f2() {
    throw std::runtime_error("test f2()");
}

class thread_guard {
    std::thread& t;
    public:
        explicit thread_guard(std::thread& t_) : t{t_} {}
        ~thread_guard() {
            std::puts("~thread_guard");
            if (t.joinable()) {
                t.join();
            }
        }
        thread_guard(thread_guard const&) = delete;
        thread_guard& operator=(thread_guard const&) = delete;
};

void f() {
    int n = 0;
    std::thread t{func{n}, 100};
    thread_guard g{t};
    f2();
}

TEST_CASE("Test Concurrent 006") {
    try {
        f();
    } catch (const std::exception& e) {
        std::cout << std::format("{}", e.what()) << std::endl;
    }

    // f();
}