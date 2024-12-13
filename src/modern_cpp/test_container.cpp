#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <cassert>

#include <iostream>
#include <complex>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

TEST_CASE("testing Demo") {

}

class Point final {
public:
    Point(int a) noexcept : x{a} {
        std::cout << "ctor " << x << std::endl;
    }

    Point() noexcept {
        std::cout << "ctor" << std::endl;
    }

    ~Point() noexcept {
        std::cout << "dtor" << std::endl;
    }

    Point(const Point& p) noexcept {
        x = p.x;
        std::cout << "copy ctor " << x << std::endl;
    }

    Point(Point&& p) noexcept {
        x = std::move(p.x);
        std::cout << "move ctor " << x << std::endl;
    }

public:
    int x = 0;
};


TEST_CASE("testing Container Case01") {
    std::vector<Point> v;
    v.reserve(10);
    Point p;
    v.push_back(p);
    v.push_back(std::move(p));
    v.emplace_back(1);
}


TEST_CASE("testing Container Case02") {
    std::array<int, 2> arr;
    assert(arr.size() == 2);

//    std::vector<int> v{2};
    std::vector<int> v(2);
    for (int i = 0; i < 10; i++) {
        v.emplace_back(i);
    }
    assert(v.size() == 12);

    deque<int> d;
    d.emplace_back(9);
    d.emplace_front(1);
    assert(d.size() == 2);

}

bool operator<(const Point& a, const Point& b) {
        return a.x < b.x;
}

TEST_CASE("testing Container Case03") {
    set<Point> s;
    s.emplace(7);
    s.emplace(3);

    for (auto& p : s) {
        cout << p.x << ",";
    }
    cout << endl;
}

TEST_CASE("testing Container Case04") {
    set<int> s= {7, 3, 9};
    for (auto& x : s) {
        cout << x << ",";
    }
    cout << endl;

    auto comp = [](auto a, auto b) {
        return a > b;
    };
    set<int, decltype(comp)> s2(comp);
    std::copy(begin(s), end(s), inserter(s2, s2.end()));

    for (auto& x : s2) {
        cout << x << ",";
    }
    cout << endl;
}

TEST_CASE("testing Container Case05") {
    unordered_map<int, string> dict;
    dict[1] = "one";
    dict.emplace(2, "two");
    dict[10] = "ten";

    for (auto& x : dict) {
        cout << x.first << " = " << x.second << ",";
    }
    cout << endl;
}

bool operator==(const Point& a, const Point& b) {
        return a.x == b.x;
}


TEST_CASE("testing Container Case06")  {
    auto haser = [](const Point& p) {
        return p.x;
    };
    unordered_set<Point, decltype(haser)> s(10, haser);

    s.emplace(7);
    s.emplace(3);

    for (auto& p : s) {
        cout << p.x << ",";
    }
    cout << endl;
}