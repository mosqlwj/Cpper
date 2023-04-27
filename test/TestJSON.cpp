//
// Created by liwenjie on 2023/4/18.
//
#include "json.hpp"
#include <fstream>
#include <iostream>
int main() {
    using json = nlohmann::json;

    // ...

    std::ifstream f("G:\\EDA\\EDA-ICTest\\morder-cpp\\data\\example.json");
    json data = json::parse(f);
    std::cout << data.at("pi") << std::endl;
    return 0;
}