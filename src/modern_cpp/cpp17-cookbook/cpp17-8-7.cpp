//
// Created by liwenjie on 25-7-1.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h" // 引入 Doctest 单元测试框架

#include <iostream> // 用于标准输入输出 (cout)
#include <memory>   // 引入 std::unique_ptr 和 std::make_unique
#include <string>   // 用于 std::string
#include <utility>  // 用于 std::move

// 明确指定要使用的 std 命名空间中的成员，提高代码可读性
using std::cout;
using std::endl;
using std::string;
using std::unique_ptr;
using std::make_unique;
using std::move;

// --- 辅助类定义 ---

// Foo 类，其构造和析构函数会打印信息，用于观察生命周期
class Foo {
public:
    string name;

    // 构造函数：打印信息，并使用移动语义初始化 name
    Foo(string n)
        : name{move(n)} {
        cout << "CTOR " << name << '\n';
    }

    // 析构函数：打印信息
    ~Foo() {
        cout << "DTOR " << name << '\n';
    }

    // 禁用拷贝构造和拷贝赋值，确保 Foo 实例只能移动或独占
    Foo(const Foo&) = delete;
    Foo& operator=(const Foo&) = delete;

    // 允许移动构造和移动赋值
    Foo(Foo&&) = default;
    Foo& operator=(Foo&&) = default;
};

// --- 辅助函数 ---

/**
 * @brief 接收一个 unique_ptr 的所有权并处理其指向的对象。
 * 当函数返回时，参数 p 所指向的 Foo 对象会被自动销毁。
 * @param p 拥有 Foo 对象所有权的 unique_ptr。
 */
void process_item(unique_ptr<Foo> p) {
    if (!p) {
        cout << "传入了一个空的 unique_ptr。\n";
        return;
    }
    cout << "正在处理： " << p->name << '\n';
    // p 在此函数作用域结束时自动析构，从而删除其管理的 Foo 对象
}

// --- Doctest 测试案例 ---

TEST_CASE("StdUniquePtr_8-7") {
    cout << "\n--- unique_ptr 基本管理与生命周期测试开始 ---\n";

    SUBCASE("块作用域内的 unique_ptr 管理") {
        cout << "--- 测试: 块作用域内的 unique_ptr ---\n";
        // 在此块内创建的 unique_ptr 会在此块结束时自动销毁
        {
            unique_ptr<Foo> p1{new Foo{"foo"}}; // 使用裸 new (不推荐)
            auto p2 = make_unique<Foo>("bar");  // 推荐使用 make_unique
            CHECK(p1->name == "foo");
            CHECK(p2->name == "bar");
            // Foo("bar") 和 Foo("foo") 将在此处被析构
        } // p1 和 p2 离开作用域，自动释放内存

        // 验证析构顺序（反向）
        // Doctest 无法直接捕获 cout 输出，但我们可以观察运行结果
        CHECK(true); // 占位符，表示测试逻辑通过控制台输出验证
    }

    SUBCASE("将新的 unique_ptr 传入函数") {
        cout << "\n--- 测试: 将新的 unique_ptr 传入函数 ---\n";
        // make_unique 创建的对象所有权立即转移给 process_item 的参数
        process_item(make_unique<Foo>("foo1"));
        // Foo("foo1") 会在 process_item 返回后立即被析构
        CHECK(true); // 占位符
    }

    SUBCASE("移动已存在的 unique_ptr 的所有权") {
        cout << "\n--- 测试: 移动已存在的 unique_ptr 的所有权 ---\n";
        auto p1_main = make_unique<Foo>("foo2");
        auto p2_main = make_unique<Foo>("foo3");

        CHECK(p1_main->name == "foo2");
        CHECK(p2_main->name == "foo3");

        process_item(move(p1_main)); // 将 p1_main 的所有权移动到 process_item

        CHECK_FALSE(p1_main); // 验证 p1_main 已经被移动，现在为空
        CHECK(p2_main->name == "foo3"); // 验证 p2_main 仍然有效

        // Foo("foo2") 会在 process_item 返回后立即被析构
        // Foo("foo3") 将在 main 函数结束时被析构
        cout << "End of SUBCASE '移动已存在的 unique_ptr 的所有权'\n";
    }

    SUBCASE("unique_ptr 的非拷贝性") {
        cout << "\n--- 测试: unique_ptr 的非拷贝性 ---\n";
        auto original_ptr = make_unique<Foo>("non_copyable");
        CHECK(original_ptr.get() != nullptr);

        // 尝试拷贝 unique_ptr 会导致编译错误，无法在这里直接测试
        // unique_ptr<Foo> copy_ptr = original_ptr; // 这行代码会导致编译错误！
        CHECK(true); // 占位符，表示概念上无法拷贝
    }

    SUBCASE("unique_ptr 的解引用与空检查") {
        cout << "\n--- 测试: unique_ptr 的解引用与空检查 ---\n";
        unique_ptr<Foo> ptr_with_value = make_unique<Foo>("valid_foo");
        CHECK(ptr_with_value.get() != nullptr);
        CHECK(static_cast<bool>(ptr_with_value) == true); // 隐式转换为 bool
        CHECK(ptr_with_value->name == "valid_foo"); // 使用 -> 运算符
        CHECK((*ptr_with_value).name == "valid_foo"); // 使用 * 运算符

        unique_ptr<Foo> empty_ptr; // 默认构造为空
        CHECK(empty_ptr.get() == nullptr);
        CHECK_FALSE(empty_ptr); // 隐式转换为 bool

        // 尝试解引用空 unique_ptr 会导致运行时错误 (未定义行为)
        // CHECK(empty_ptr->name == ""); // DO NOT DO THIS!
        // CHECK_THROWS_AS(empty_ptr->name, ...); // 无法捕获这种未定义行为
        process_item(move(empty_ptr)); // 测试传入空指针给函数

        CHECK(true); // 占位符
    }

    SUBCASE("unique_ptr::reset() 方法") {
        cout << "\n--- 测试: unique_ptr::reset() 方法 ---\n";
        auto p = make_unique<Foo>("original");
        CHECK(p->name == "original");

        // reset() 会先删除当前对象，再接管新对象
        p.reset(new Foo("new_one"));
        CHECK(p->name == "new_one");

        // reset() 不带参数会释放当前对象并设置为空
        p.reset();
        CHECK_FALSE(p); // 验证为空
        CHECK(p.get() == nullptr); // 验证裸指针为空

        CHECK(true); // 占位符
    }

    cout << "--- unique_ptr 基本管理与生命周期测试结束 ---\n\n";
}