#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h" // 引入 Doctest 单元测试框架

#include <iostream>   // 用于标准输入输出 (cout, endl)
#include <iomanip>    // 用于 std::quoted (C++14)，打印带引号字符串
#include <tuple>      // 引入 std::tuple
#include <functional> // 引入 std::apply (C++17)
#include <string>     // 引入 std::string
#include <list>       // 用于存储多个元组的容器 (std::initializer_list)

// 明确指定要使用的 std 命名空间中的成员，提高代码可读性
using std::cout;
using std::endl;
using std::string;
using std::tuple;
using std::quoted;    // C++14: 打印字符串时自动加引号
using std::make_tuple;
using std::apply;     // C++17: 将元组元素作为参数应用于函数
using std::initializer_list; // 用于定义列表字面量
using namespace std::string_literals;
// --- 待应用于元组元素的函数 ---

/**
 * @brief 打印学生信息。
 * @param id 学生的 ID。
 * @param name 学生的姓名。
 * @param gpa 学生的 GPA。
 */
static void print_student(size_t id, const string &name, double gpa) {
    cout << "学生 " << quoted(name) // 使用 quoted 确保姓名被正确引用
         << ", ID: " << id
         << ", GPA: " << gpa << '\n';
}

// --- Doctest 测试案例 ---

// 这个 TEST_CASE 演示了 std::tuple 的多种解包方式，并突出 std::apply 的优雅之处。
TEST_CASE("StdApply_元组与函数的应用") {
    cout << "\n--- std::apply 示例开始 ---\n";

    // 1. 定义一个元组类型别名，用于表示学生数据 (ID, 姓名, GPA)
    using student = tuple<size_t, string, double>;

    // 2. 创建一个学生元组实例
    // "s" 后缀是 C++14 的用户定义字符串字面量，用于直接创建 std::string
    student john {123, "张三"s, 3.7};

    // --- 方法 1: 使用 C++17 结构化绑定进行传统解包 ---
    // 这种方式需要知道元组的结构，并将元素解包到命名变量中。
    cout << "\n--- 方法 1: C++17 结构化绑定解包 ---\n";
    { // 使用块作用域限制解包变量的生命周期
        const auto &[id, name, gpa] = john; // 结构化绑定将元组元素解包
        print_student(id, name, gpa);       // 使用解包后的变量调用函数
        // 验证一个简单的条件来确保测试案例运行成功
        CHECK(id == 123);
        CHECK(name == "张三");
        CHECK(gpa == 3.7);
    }

    // 3. 创建一个包含多个学生元组的列表，用于循环演示
    initializer_list<student> arguments_for_later = {
        make_tuple(234, "李四"s, 3.7),
        make_tuple(345, "王五"s, 4.0),
        make_tuple(456, "赵六"s, 3.5),
    };

    // --- 方法 2: 循环中使用 C++17 结构化绑定进行传统解包 ---
    // 与方法 1 类似，循环中的每次迭代都需要了解元组结构。
    cout << "\n--- 方法 2: 循环中结构化绑定解包 ---\n";
    for (const auto &[id, name, gpa] : arguments_for_later) {
           print_student(id, name, gpa);
           // 对于循环中的每个元素，可以添加额外的检查
           CHECK(id > 0); // 简单检查 ID 是否有效
    }

    // --- 方法 3: 使用 std::apply 进行优雅的元组应用 (针对单个元组) ---
    // std::apply 接收一个可调用对象（如函数指针）和一个元组。
    // 它会自动解包元组元素并将其作为参数传递给可调用对象，无需手动解包。
    // 这种方法更通用，对元组的具体结构依赖更小。
    cout << "\n--- 方法 3: 使用 std::apply 解包单个元组 ---\n";
    apply(print_student, john);
    // 无法直接对 apply 的返回值进行 CHECK（因为 print_student 返回 void），
    // 但可以检查其副作用（如打印输出是否正确），或者封装在其他可测试的函数中。
    CHECK(true); // 简单检查表示此部分代码按预期执行

    // --- 方法 4: 循环中使用 std::apply 进行元组应用 ---
    // 展示了 std::apply 如何简化在循环中将元组内容传递给函数。
    cout << "\n--- 方法 4: 循环中使用 std::apply 解包多个元组 ---\n";
    for (const auto &args : arguments_for_later) {
        apply(print_student, args);
        CHECK(true); // 简单检查表示此部分代码按预期执行
    }

    cout << "--- std::apply 示例结束 ---\n\n";
}