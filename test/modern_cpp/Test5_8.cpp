// Standard Library Existence Queries

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <vector>
#include <algorithm>
#include <ranges>

TEST_CASE("testing case01") {
    std::vector<int> v{0,2,9,1,3,8,5,2,9};
    auto const check = [](int x) { return x>= 1; };

    std::cout << "res:" << std::all_of(std::begin(v), std::begin(v), check) << "\n";
    std::cout << "res:" << std::any_of(std::begin(v), std::begin(v), check) << "\n";
    std::cout << "res:" << std::none_of(std::begin(v), std::begin(v), check) << "\n";
    
    std::cout << "res:" << std::ranges::all_of(v, check) << "\n";
    std::cout << "res:" << std::ranges::any_of(v, check) << "\n";
    std::cout << "res:" << std::ranges::none_of(v, check) << "\n";
    

}


TEST_CASE("testing case02") {
    std::vector<int> v {5,2,9,1,3,2,5,2,2,9};

    // count in subrange (as shown in image):
    auto n = count(begin(v)+1, begin(v)+8, 2);  // n = 3
    std::cout << "n: " << n << '\n';

    // count in entire vector:
    auto m = count(begin(v), end(v), 2);  // m = 4
    std::cout << "m: " << m << '\n';


    std::vector<int> v1 {2,9,1,3,2,5,2};

    std::cout << std::ranges::count(v1, 3) << '\n';  // 1
    std::cout << std::ranges::count(v1, 2) << '\n';  // 3
    std::cout << std::ranges::count(v1, 7) << '\n';  // 0
    
}

TEST_CASE("testing case03") {


    std::vector<int> v {4,9,1,3,2,5,6};

    auto const is_even = [](int x) {   return !(x & 1); };
    auto n = std::ranges::count_if(v, is_even);  // n = 3
    std::cout << "n: " << n << '\n';


}





