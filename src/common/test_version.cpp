#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "config.h"

#include <iostream>


TEST_CASE("Test Version") {
    std::cout << "Major version number:" << PROJECT_VERSION_MAJOR << std::endl;
    std::cout << "Minor version number:" << PROJECT_VERSION_MINOR << std::endl;
    std::cout << "Patch version number:" << PROJECT_VERSION_PATCH << std::endl;
}

