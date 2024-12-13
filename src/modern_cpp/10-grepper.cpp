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

// 函数matches：在指定文件中寻找正则表达式匹配的行，并返回匹配行的行号和内容
static vector<pair<size_t, string>> matches(const fs::path &p, const regex &re) {
    vector<pair<size_t, string>> matchesList; // 存储匹配结果的向量

    // 打开文件
    ifstream inputFile(p);

    string lineContent; // 用于存储每一行的内容
    for (size_t lineNumber = 1; getline(inputFile, lineContent); ++lineNumber) { // 逐行读取文件
        if (regex_search(lineContent.begin(), lineContent.end(), re)) { // 如果当前行与正则表达式匹配
            matchesList.emplace_back(lineNumber, std::move(lineContent)); // 将行号和行内容加入结果向量
        }
    }

    return matchesList; // 返回所有匹配结果
}

int main(int argc, char *argv[]) {
    if (argc != 2) { // 检查命令行参数是否正确
        cout << "Usage: " << argv[0] << " <pattern>\n"; // 打印使用说明
        return 1; // 错误返回码
    }

    regex pattern; // 正则表达式对象
    try {
        pattern = regex{argv[1]}; // 尝试根据输入参数构造正则表达式
    } catch (const regex_error &e) { // 捕获正则表达式构造异常
        cout << "Invalid regular expression provided.\n"; // 打印错误信息
        return 1; // 错误返回码
    }

    // 遍历当前目录及其子目录下所有文件
    for (const auto &entry : fs::recursive_directory_iterator(fs::current_path())) {
        if (!entry.is_regular_file()) continue; // 优化：仅处理常规文件，跳过目录和其他类型文件
        auto matchesList = matches(entry.path(), pattern); // 对每个文件调用matches函数

        // 输出匹配结果
        for (const auto &[lineNumber, content] : matchesList) {
            cout << entry.path() << ":" << lineNumber << " - " << content << '\n';
        }
    }

    return 0;
}