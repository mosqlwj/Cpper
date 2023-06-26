// Function Object

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <vector>
#include <algorithm>
#include <ranges>


TEST_CASE("testing demo") {
   
    std::cout << "Hello" << "\n";
}


class in_interval {
    int a_;
    int b_;
public:
    explicit constexpr
    in_interval(int a, int b) noexcept : a_{a}, b_{b} {}

    [[nodiscard]] constexpr
    bool operator() (int x) const noexcept {
        return x >= a_ && x <= b_;
    }
};

TEST_CASE("testing Interval Query") {
    in_interval test{-10, 5};
    std::cout << test(1) << "\n";
    std::cout << test(5) << "\n";
    std::cout << test(-12) << "\n";
    std::cout << test(8) << "\n";
}


TEST_CASE("testing Finding in Interval") {
    std::vector<int> v{9, 0, 4, 1, 8, 3, 7, 2, 9};
    auto i = std::ranges::find_if(std::begin(v) + 2, std::begin(v) + 7, in_interval{6, 8});
    if (i != std::end(v)) {
        auto value = *i;
        auto index = std::ranges::distance(std::begin(v), i);
        std::cout << value << " , " << index << "\n";
    }
}

TEST_CASE("testing Partitioning with Intervals") {
    std::vector<int> v{9, 0, 4, 1, 8, 3, 7, 2, 9};
    auto i = std::partition(std::begin(v), std::end(v), in_interval{6, 8});
    std::for_each(std::begin(v), i, [](int x){   std::cout << x << ' '; }); 
    std::cout << "\n";
    std::for_each(i, std::end(v), [](int x){   std::cout << x << ' '; }); 
}

#include <functional>
#include <set>
TEST_CASE("testing Comparisons") {
   
    std::set<int, std::greater<>> s;
    std::vector<int> v1{1, 4, 5};
    std::vector<int> v2 {1, 2, 5};

    std::cout << std::lexicographical_compare(std::begin(v1), std::end(v1), 
                                              std::begin(v1), std::end(v1), std::greater<>{});
}


