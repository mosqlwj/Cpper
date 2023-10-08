// standord algorithms introduction

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <vector>
#include <algorithm>

TEST_CASE("testing hello") {
    
}

TEST_CASE("testing typeid") {
    std::cout << "Hello" << std::endl;
    int x1 = 0;
    double x2 = 5.5;
    std::cout << typeid(x1).name() << std::endl;
    std::cout << typeid(x1 + x2).name() << std::endl;
    std::cout << typeid(int).name() << std::endl;

    // auto t1 = typeid(int);
    auto& t2 = typeid(int);
    auto t3 = &typeid(int);
}


TEST_CASE("testing decltype1") {
    int x1 = 0;
    decltype(x1) x2 = 0;
    std::cout << typeid(x2).name() << "\n";

    double x3 = 1.3;
    decltype(x1 + x3) x4 = x1 + x3;
    std::cout << typeid(x4).name() << "\n";

    // decltype({1, 2}) x5;
    decltype(1) x5;
}

// template<class T>
// auto return_ref(T& t) {
//     return t;
// }

template<class T>
auto return_ref(T& t)->decltype(t) {
    return t;
}

TEST_CASE("testing decltype2") {
    int x1 = 0;
    static_assert(std::is_reference_v<decltype(return_ref(x1))>);
}