#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h" // 引入 Doctest 单元测试框架

#include <iostream>   // 用于标准输入输出
#include <optional>   // 用于 std::optional
#include <string>     // 用于 std::string
#include <limits>     // 用于 std::numeric_limits，清除输入流错误
#include <iomanip>    // 用于输入流操作（std::fixed, std::setprecision, std::setw）

// 明确指定要使用的 std 命名空间中的成员，提高可读性并避免潜在冲突
using std::cout;
using std::cin;
using std::endl;
using std::optional;

// --- 自定义类型别名和辅助函数 ---

// 定义 'oint' 作为 optional<int> 的别名，简化代码书写
using oint = optional<int>;

/**
 * @brief 安全地从标准输入读取一个整数。
 * @return 如果成功读取到整数，则返回一个包含该整数的 optional<int> 对象；
 * 如果输入失败（例如，输入了非数字字符），则返回一个空的 optional 对象。
 */
oint read_int() {
    int i;
    if (cin >> i) { // 尝试从输入流读取整数
        return {i}; // 成功读取，返回包含该值的 optional 对象
    }
    // 如果读取失败 (cin 处于错误状态，如用户输入了非数字)
    cin.clear(); // 清除输入流的错误标志
    // 忽略并丢弃当前行中剩余的所有字符，直到遇到换行符为止，防止后续读取继续失败
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return {}; // 返回一个空的 optional 对象，表示未成功获取值
}

/**
 * @brief 为两个 optional<int> 对象重载 + 运算符。
 * @return 如果两个 optional 都包含值，则返回一个包含它们和的新 optional<int>；
 * 否则，返回一个空的 optional。
 */
oint operator+(oint a, oint b) {
    if (!a || !b) { // 如果任一操作数为空（不包含值）
        return {};  // 结果也为空
    }
    // 两个操作数都包含值，解引用并求和
    return {*a + *b};
}

/**
 * @brief 为一个 optional<int> 和一个普通 int 重载 + 运算符。
 * @return 如果 optional 包含值，则返回一个包含它们和的新 optional<int>；
 * 否则，返回一个空的 optional。
 */
oint operator+(oint a, int b) {
    if (!a) { // 如果 optional 操作数为空
        return {}; // 结果为空
    }
    // optional 包含值，解引用并与普通 int 求和
    return {*a + b};
}

// --- Doctest 测试案例 ---

// 这个 TEST_CASE 演示了 std::optional 在交互式场景中的用法。
// 尽管单元测试通常是非交互式的，但这种结构允许通过 doctest 框架运行此示例的用户交互。
TEST_CASE("StdOptional_安全输入与求和") {
    cout << "\n--- std::optional 示例开始 ---\n";
    cout << "请输入 2 个整数。（例如：'1 2' 或 '5 hello'）\n";
    cout << "您也可以输入无效字符或按 Ctrl+D (Unix) / Ctrl+Z (Windows) 后回车来触发失败。\n> ";

    // 从用户输入中读取两个可选整数
    auto a = read_int();
    auto b = read_int();

    // 执行求和操作：a + b + 10。
    // 我们重载的运算符透明地处理了 optional 的逻辑。
    auto sum = a + b + 10;

    // 检查最终的 sum optional 是否包含值。
    // std::optional 可以隐式转换为 bool 类型（包含值时为 true，为空时为 false）。
    if (sum) {
        // 如果 sum 包含值，意味着 'a' 和 'b' 也都包含值，此时可以安全地解引用它们。
        cout << *a << " + " << *b << " + 10 = " << *sum << '\n';
        // 在这里可以添加 Doctest 的 CHECK 宏来验证特定已知输入的结果。
        // 例如：CHECK(*sum == (预期_a + 预期_b + 10));
        CHECK(true); // 表示测试案例的此路径成功完成
    } else {
        // 如果 sum 为空，意味着至少一个输入无效。
        cout << "抱歉，输入不是 2 个数字。无法计算总和。\n";
        CHECK(true); // 表示测试案例的此错误处理路径按预期执行
    }
    cout << "--- std::optional 示例结束 ---\n\n";
}

// --- 附加示例：演示 value_or 和 bad_optional_access ---
// 这部分代码仅用于演示，并非上述主要交互式测试案例的一部分。
TEST_CASE("StdOptional_值或默认值与错误访问") {
    cout << "\n--- 演示 std::optional::value_or 和 bad_optional_access ---\n";

    // 示例 1: value_or - 提供一个默认值
    optional<int> maybe_num = {}; // 一个空的 optional 对象
    int result = maybe_num.value_or(99); // 如果 optional 为空，则使用 99
    cout << "空的 optional.value_or(99): " << result << '\n';
    CHECK(result == 99);

    maybe_num = 123; // 现在 optional 包含一个值
    result = maybe_num.value_or(99); // optional 包含值，使用其自身的值 123
    cout << "包含值的 optional.value_or(99): " << result << '\n';
    CHECK(result == 123);

    // 示例 2: 捕获 std::bad_optional_access 异常
    cout << "请为 bad_optional_access 测试输入 1 个数字（或非数字以触发失败）：\n> ";
    optional<int> val = read_int(); // 尝试读取一个数字

    try {
        // 尝试直接访问 optional 的值，而不检查它是否存在。
        // 如果 'val' 为空，这一行将抛出 std::bad_optional_access 异常。
        cout << "成功访问值: " << val.value() << '\n';
        CHECK(true); // 如果没有抛出异常，表示测试通过此部分
    } catch (const std::bad_optional_access& e) {
        // 捕获到 std::bad_optional_access 异常
        cout << "捕获到异常: " << e.what() << "（如果输入无效，这是预期行为）\n";
        CHECK(true); // 如果捕获到异常，表示异常处理按预期工作
    }
    cout << "--- std::optional::value_or 和 bad_optional_access 演示结束 ---\n\n";
}