#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h" // 引入 Doctest 单元测试框架

#include <iostream>   // 用于标准输入输出 (cout)
#include <iomanip>    // 用于 std::quoted (C++14)，打印带引号字符串
#include <list>       // 用于 std::list
#include <any>        // 引入 std::any (C++17)
#include <iterator>   // 用于 std::ostream_iterator，辅助打印列表
#include <string>     // 用于 std::string (特别是 "s" 字面量后缀)

// 明确指定要使用的 std 命名空间中的成员，提高代码可读性
using std::cout;
using std::endl;
using std::string;
using std::list;
using std::any;
using std::quoted;
using std::any_cast;     // 用于从 std::any 中提取值
using std::type_info;    // 用于类型比较
using std::in_place_type_t; // 用于就地构造 std::any
using std::ostream_iterator;
using namespace std::string_literals; // 引入 "s" 字符串字面量后缀

// --- 类型别名 ---

// 为 list<int> 定义类型别名，简化代码书写
using int_list = list<int>;

// --- 核心函数 ---

/**
 * @brief 打印 std::any 中存储的任何类型的值。
 * 如果 std::any 为空，或者类型不被识别，则打印相应提示。
 * @param a 待打印的 std::any 对象（const 引用以避免不必要的拷贝）。
 */
void print_anything(const std::any &a) {
    // 1. 检查 std::any 是否包含值
    if (!a.has_value()) {
        cout << "内容：无。\n";
    }
    // 2. 类型检查与转换：使用 a.type() 与 typeid(T) 进行比较，并使用 any_cast 安全转换。
    else if (a.type() == typeid(string)) { // 如果是 string 类型
        // any_cast<const string&> 提取 string 的常量引用，避免拷贝
        cout << "内容：是一个字符串：" << quoted(any_cast<const string&>(a)) << '\n';
    } else if (a.type() == typeid(int)) { // 如果是 int 类型
        // any_cast<int> 提取 int 的值（对于基本类型拷贝开销很小）
        cout << "内容：是一个整数：" << any_cast<int>(a) << '\n';
    } else if (a.type() == typeid(int_list)) { // 如果是 int_list 类型
        // any_cast<const int_list&> 提取 int_list 的常量引用，避免列表拷贝
        const auto &l = any_cast<const int_list&>(a);
        cout << "内容：是一个整数列表：";
        // 使用 ostream_iterator 辅助打印列表元素，用逗号分隔
        std::copy(std::begin(l), std::end(l), ostream_iterator<int>{cout, ", "});
        cout << '\n';
    }
    // 3. 处理未知类型：如果以上类型均不匹配，则打印无法处理的提示。
    else {
        cout << "内容：无法处理此项。（类型名称：" << a.type().name() << "）\n";
    }
}

// --- Doctest 测试案例 ---

/**
 * @brief 演示 std::any 的基本用法、类型检查和就地构造。
 * 通过打印不同类型的数据来验证其功能。
 */
TEST_CASE("StdAny_8-5") {
    cout << "\n--- std::any 基础用法演示开始 ---\n";

    // 1. 演示空 std::any
    cout << "测试 1：空 std::any\n";
    print_anything({});
    CHECK_FALSE(any{}.has_value()); // 验证空 optional 不包含值

    // 2. 演示 std::string 类型
    cout << "测试 2：std::string 类型\n";
    print_anything("Hello World!"s);
    CHECK(any("Test"s).type() == typeid(string)); // 验证类型识别

    // 3. 演示 int 类型
    cout << "测试 3：int 类型\n";
    print_anything(42);
    CHECK(any(100).type() == typeid(int)); // 验证类型识别

    // 4. 演示自定义 int_list 类型
    cout << "测试 4：int_list 类型\n";
    print_anything(int_list{10, 20, 30});
    CHECK(any(int_list{1}).type() == typeid(int_list)); // 验证类型识别

    // 5. 演示使用 in_place_type_t 就地构造 std::any
    cout << "测试 5：使用 in_place_type_t 就地构造 int_list\n";
    print_anything(any(in_place_type_t<int_list>{}, {5, 4, 3, 2, 1}));
    CHECK(any(in_place_type_t<int_list>{}, std::initializer_list<int>{}).type() == typeid(int_list));; // 验证就地构造后的类型

    // 6. 演示无法处理的类型 (double)
    cout << "测试 6：无法处理的 double 类型\n";
    print_anything(3.14159); // double 类型未在 print_anything 中明确处理
    CHECK(any(3.14).type() == typeid(double)); // 验证类型识别为 double

    cout << "--- std::any 基础用法演示结束 ---\n\n";
}

/**
 * @brief 演示 std::any 的错误处理机制：std::bad_any_cast 异常。
 */
TEST_CASE("StdAny_错误处理_bad_any_cast") {
    cout << "\n--- std::any 错误处理演示开始 ---\n";

    any val_int = 123; // 存储一个 int
    any val_string = "hello"s; // 存储一个 string

    // 尝试正确转换
    CHECK(any_cast<int>(val_int) == 123);
    CHECK(any_cast<const string&>(val_string) == "hello");

    // 尝试错误转换：从 int 转换为 string，预期抛出 bad_any_cast
    CHECK_THROWS_AS(any_cast<string>(val_int), std::bad_any_cast);
    // 尝试错误转换：从 string 转换为 int，预期抛出 bad_any_cast
    CHECK_THROWS_AS(any_cast<int>(val_string), std::bad_any_cast);

    // 尝试访问空 any，预期抛出 bad_any_cast (通过 value() 访问)
    any empty_any;
    CHECK_THROWS_AS(any_cast<int>(empty_any), std::bad_any_cast);

    cout << "--- std::any 错误处理演示结束 ---\n\n";
}