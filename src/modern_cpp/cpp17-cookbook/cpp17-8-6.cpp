#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h" // 引入 Doctest 单元测试框架

#include <iostream>   // 用于标准输入输出 (cout)
#include <variant>    // 引入 std::variant (C++17)
#include <list>       // 用于 std::list
#include <string>     // 用于 std::string
#include <algorithm>  // 用于 std::count_if

// 明确指定要使用的 std 命名空间中的成员，提高代码可读性
using std::cout;
using std::endl;
using std::string;
using std::list;
using std::variant;
using std::holds_alternative; // 用于检查 variant 是否持有特定类型
using std::get;               // 用于获取 variant 中的值
using std::get_if;            // 用于安全获取 variant 中的值（返回指针）
using std::visit;             // 用于访问 variant 中的值
using std::count_if;          // 用于统计满足条件的元素数量

// --- 动物类定义 ---

// 定义 Cat 类，具有名字和 meow() 方法
class cat {
    string name;
public:
    // 使用 std::move 优化字符串构造
    cat(string n) : name{std::move(n)} {}
    void meow() const {
        cout << name << " 说：喵！\n";
    }
    // 添加一个用于测试的 getter，Doctest 中可能需要
    const string& get_name() const { return name; }
};

// 定义 Dog 类，具有名字和 woof() 方法
class dog {
    string name;
public:
    // 使用 std::move 优化字符串构造
    dog(string n) : name{std::move(n)} {}
    void woof() const {
        cout << name << " 说：汪！\n";
    }
    // 添加一个用于测试的 getter，Doctest 中可能需要
    const string& get_name() const { return name; }
};

// --- 类型别名与辅助函数/结构体 ---

// 定义 animal 类型别名，表示它可以是 dog 或 cat 中的一种
using animal = variant<dog, cat>;

// 辅助函数：判断 variant 是否持有特定类型
template <typename T>
bool is_type(const animal &a) {
    return holds_alternative<T>(a);
}

// 辅助结构体：一个函数对象，用于对 variant 中的 dog 或 cat 类型执行相应操作。
// 它通过重载 operator() 来实现对不同类型的处理。
struct animal_voice {
    void operator()(const dog &d) const { d.woof(); }
    void operator()(const cat &c) const { c.meow(); }
};

// --- Doctest 测试案例 ---

TEST_CASE("StdVariant_8-6") {
    cout << "\n--- std::variant 基础用法演示开始 ---\n" << endl;

    // 1. 创建一个包含 cat 和 dog 实例的 animal 类型列表
    // 注意：这里的 string 字面量无需 's' 后缀，因为 cat/dog 构造函数接受 std::string
    list<animal> animals_list {cat{"图拔"}, dog{"巴鲁"}, cat{"波比"}};

    SUBCASE("访问方式 1: 使用 variant::index() 和 switch") {
        cout << "\n--- 访问方式 1: 使用 variant::index() 和 switch ---\n";
        int dog_count_idx = 0;
        int cat_count_idx = 0;
        for (const animal &a : animals_list) {
            switch (a.index()) { // 获取当前存储类型的索引
            case 0: // 索引 0 对应 dog
                get<dog>(a).woof();
                dog_count_idx++;
                CHECK(get<dog>(a).get_name() == (dog_count_idx == 1 ? "巴鲁" : "")); // 简单验证
                break;
            case 1: // 索引 1 对应 cat
                get<cat>(a).meow();
                cat_count_idx++;
                CHECK((get<cat>(a).get_name() == "图拔" || get<cat>(a).get_name() == "波比")); // 简单验证
                break;
            }
        }
        CHECK(dog_count_idx == 1);
        CHECK(cat_count_idx == 2);
    }

    SUBCASE("访问方式 2: 使用 get_if<T>() 和 if/else if") {
        cout << "\n--- 访问方式 2: 使用 get_if<T>() 和 if/else if ---\n";
        int dog_count_if = 0;
        int cat_count_if = 0;
        for (const animal &a : animals_list) {
            if (const auto d = get_if<dog>(&a); d) { // 尝试获取 dog 指针
                d->woof();
                dog_count_if++;
                CHECK(d->get_name() == "巴鲁"); // 简单验证
            } else if (const auto c = get_if<cat>(&a); c) { // 否则，尝试获取 cat 指针
                c->meow();
                cat_count_if++;
                CHECK((c->get_name() == "图拔" || c->get_name() == "波比")); // 简单验证
            }
        }
        CHECK(dog_count_if == 1);
        CHECK(cat_count_if == 2);
    }

    SUBCASE("访问方式 3: 使用 std::visit") {
        cout << "\n--- 访问方式 3: 使用 std::visit ---\n";
        // visit 的返回值通常是 void 或者访问器返回值的统一类型，不易直接 CHECK。
        // 主要检查其行为（打印输出）。
        for (const animal &a : animals_list) {
            visit(animal_voice{}, a);
        }
        CHECK(true); // 简单检查表示此部分代码按预期执行
    }

    SUBCASE("统计列表中猫和狗的数量") {
        cout << "\n--- 统计列表中猫和狗的数量 ---\n";
        long long num_cats = count_if(std::begin(animals_list), std::end(animals_list), is_type<cat>);
        long long num_dogs = count_if(std::begin(animals_list), std::end(animals_list), is_type<dog>);

        cout << "列表中有 " << num_cats << " 只猫和 " << num_dogs << " 只狗。\n";
        CHECK(num_cats == 2);
        CHECK(num_dogs == 1);
    }

    SUBCASE("错误处理: 尝试获取错误的类型") {
        cout << "\n--- 错误处理: 尝试获取错误的类型 ---\n";
        animal my_dog = dog{"Buddy"};
        // 尝试从存储 dog 的 variant 中获取 cat，预期抛出 std::bad_variant_access
        CHECK_THROWS_AS(get<cat>(my_dog), std::bad_variant_access);

        animal my_cat = cat{"Mittens"};
        // 尝试从存储 cat 的 variant 中获取 dog，预期抛出 std::bad_variant_access
        CHECK_THROWS_AS(get<dog>(my_cat), std::bad_variant_access);
    }

    cout << "--- std::variant 基础用法演示结束 ---\n\n";
}