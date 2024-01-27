#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "modern_cpp.h"

#include <vector>
#include <string>
#include <string_view>

TEST_CASE("testing MODERN CPP") {
    ModernCPP().Print();
}