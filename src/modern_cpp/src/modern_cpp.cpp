//
// Created by liwenjie on 2023/4/27.
//
#include "modern_cpp.h"

#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

void ModernCPP::Print() {
    std::cout << "Hello Modern CPP" << std::endl;

    std::ifstream f("/mnt/d/wsl_space/MosqCPP/data/example.json");
    json data = json::parse(f);
    std::cout << "json: pi is " << data["pi"] << std::endl;
}