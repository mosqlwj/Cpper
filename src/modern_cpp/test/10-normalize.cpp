//
// Created by liwenjie on 2024/5/21.
//
//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
//#include "doctest.h"
#include <cassert>

#include <iostream>
#include <filesystem>

using namespace std;
using namespace std::filesystem;

//TEST_CASE("testing Demo") {
//    std::cout << "hello Demo" << std::endl;
//
//}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <path>" << std::endl;
        return EXIT_FAILURE;
    }

    const std::filesystem::path dir{argv[1]};
    if (!std::filesystem::exists(dir)) {
        std::cout << "Path " << dir << " does not exist" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << std::filesystem::canonical(dir).c_str() << std::endl;
    return EXIT_SUCCESS;
}