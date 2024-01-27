#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <vector>
#include <string>
#include <string_view>


struct demo {
    std::string_view sv_;
};

TEST_CASE("testing string view") {
    std::string s1{"Text"};
    std::string_view sv1 {s1};
    std::cout << sv1 << "\n"; 
    using namespace std::string_literals;
    std::string_view sv2 {"std::string Literal"s};
    // std::cout << sv2; 
}