// Container Traversal

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <vector>
#include <algorithm>
#include <ranges>

TEST_CASE("testing reverse range-based loop") {
    std::vector<int> v{7, 9, 3, 5, 3, 2, 4, 1, 8, 0};
    for (int x : v | std::views::reverse) { std::cout << x << '\n'; }
    // read-only, if type cheap to copy/or copy needed
    for (auto x : v | std::views::reverse) { std::cout << x; }
    // read-only, if type expensive to copy
    for (auto const& x : v | std::views::reverse) { std::cout << x; }
    // modify values
    // for (auto& x : v | std::views::reverse) { std::cin >> x; }
}


TEST_CASE("testing reverse for each loop") {
    std::vector<int> v{7, 9, 3, 5, 3, 2, 4, 1, 8, 0};
    
    std::ranges::for_each(std::views::reverse(v), [](auto x){ 
        std::cout << x << "\n";
        });
}



TEST_CASE("testing utilities") {
    std::vector<int> v{7, 9, 3, 5, 3, 2, 4, 1, 8, 0};
    
    auto i = std::next(v.begin());
    auto j = std::next(i, 3);
}