//
// Created by liwenjie on 2023/4/18.
//
#include "json.hpp"
#include <fstream>
#include <iostream>
int main() {
    using json = nlohmann::json;

    // ...

    // std::ifstream f("/home/liwenjie/workspace/MosqCPP/data/example.json");
    // json data = json::parse(f);
    // std::cout << data.at("pi") << std::endl;

    std::ifstream f("/home/liwenjie/workspace/MosqCPP/data/func_test.json");
    json data = json::parse(f);
    std::cout << data.at("patterns").at("function_test")[0].at("cycles")[0].at("cycle") << std::endl;
    return 0;
}