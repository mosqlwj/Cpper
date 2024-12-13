//
// Created by liwenjie on 2024/5/21.
//

#include <iostream>      // 标准输入输出库
#include <fstream>       // 文件流操作库
#include <regex>         // 正则表达式库
#include <vector>        // 动态数组容器库
#include <string>        // 字符串操作库
#include <filesystem>    // 文件系统操作库（C++17及以上版本的标准库）

using namespace std;    // 使用标准命名空间以简化代码
namespace fs = std::filesystem; // C++17后推荐使用std::filesystem，这里定义别名简化调用

template <typename T>
static std::string replace(std::string str, const T& replacement) {
    for (const auto&[pat, rep] : replacement) {
        str = regex_replace(str, pat, rep);
    }
    return str;
}

int main(int argc, char *argv[]) {

    if (argc < 3 && argc % 2 != 1) {
        std::cout << "Usage: " << argv[0] << " [<pattern> <replacement>]..." << std::endl;
        return EXIT_FAILURE;
    }


    std::vector<std::pair<std::regex, std::string>> patterns;
    for ( int i = 1; i < argc; i += 2) {
        patterns.emplace_back(argv[i], argv[i + 1]);
    }

    for (auto& entry : fs::recursive_directory_iterator(fs::current_path())) {
        if (!entry.is_regular_file()) {
            continue;
        }
        fs::path opath = entry.path(); // 获取文件路径
        std::string rname = replace(opath.filename().string(), patterns);

        fs::path rpath = opath;
        rpath.replace_filename(rname); // 替换文件名

        if (opath != rpath) {
            std::cout << opath.string() << " -> " << rpath.string() << std::endl;
            if (fs::exists(rpath)) {
                std::cout << "File already exists: " << rpath.string() << std::endl;
                continue;
            } else {
                fs::rename(opath, rpath);
            }

        }
    }

    return 0;
}