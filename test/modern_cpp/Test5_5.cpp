// standord algorithms introduction

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <vector>
#include <algorithm>

TEST_CASE("testing min_element") {
    std::vector<int> v{7, 9, 3, 5, 3, 2, 4, 1, 8, 0};
    auto i = std::min_element(std::begin(v) + 2, std::begin(v) + 7);
    auto min = *i;
    std::cout << *i << "\n";
    auto j = std::min_element(std::begin(v), std::end(v));
    std::cout << *j << "\n";
    v.erase(j);
}

struct P {
    int q;
    char c;
};

bool less_q(P const& x, P const& y) {
    return x.q < y.q;
}

TEST_CASE("testing Callable Parameters") {
    std::vector<P> v{{2, 'c'}, {1, 'b'}, {3, 'a'}};
    // auto i = std::min_element(std::begin(v), std::end(v), less_q);
    auto i = std::min_element(std::begin(v), std::end(v), 
        [](P const& x, P const& y){
            return x.q < y.q;
        });
    std::cout << i->q << "/" << i->c << "\n";
}