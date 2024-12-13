//
// Created by liwenjie on 2024/4/7.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

using namespace  std;

void my_square(int x) {
    cout << x * x << endl;
}

TEST_CASE("Testing Lambda Case01") {
    auto pfunc = &my_square;
    (*pfunc)(3);
    pfunc(3);

    auto func = [](int x) {
        cout << x * x << endl;
    };
    func(3);
}

TEST_CASE("Testing Lambda Case02") {
   int n = 10;
   auto func = [=](int x) {
       cout << x * n << endl;
   };
   func(3);
}

TEST_CASE("Testing Lambda Case03") {
    auto f1 = [](){};
    auto f2 = []() {
        cout << "lambda f2" << endl;
        auto f3 = [](int x) {
            return x * x;
        };
        cout << f3(3) << endl;
    };
    f1();
    f2();
//    f3();
    vector<int> v = {3, 1, 8, 5, 0};
    cout << *find_if(v.begin(), v.end(),
                     [](int x) {
                        return x >= 5;
                    })
         << endl;
}

TEST_CASE("Testing Lambda Case04") {
    int x = 33;
    auto f1 = [=]() {
        cout << x << endl;
    };

    int n = 10;
    auto f2 = [&]() {
        x += 10;
        cout << n << endl;
    };

    auto f3 = [=, &x]() {
        x += 20;
    };

    f1();
    f2();
    cout << x << endl;
    f3();
    cout << x << endl;
}

class DemoLambda final {
public:
    auto print() {
        return [this]() {
            cout << "member: " << x << endl;
        };
    }
private:
    int x = 10;
};

TEST_CASE("Testing Lambda Case05") {
    DemoLambda obj;
    auto f = obj.print();
    f();
}

TEST_CASE("Testing Lambda Case06") {
    auto f = [](const auto& x) {
        return x + x;
    };

    cout << f(3) << endl;
    cout << f(3.14) << endl;
//    cout << f("matrix") << endl;
    cout << f(string("matrix")) << endl;
}