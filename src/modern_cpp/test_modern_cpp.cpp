#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"



#include <vector>
#include <string>
#include <string_view>
#include <iostream>
#include <utility> // for std::forward
#include <type_traits>
#include <algorithm>
#include <format>
#include <tuple>

/**
 * 本cpp文件，用于测试吴咏伟的现代C++编程
 */

TEST_CASE("Testing Modern CPP") {

}

/////////////////////////////////
//堆，栈

class Obj {
public:

    Obj() { puts("Obj()"); }
    ~Obj() { puts("~Obj()"); }
};

// 无论是否发生异常，都会调用析构函数，释放栈上的对象
void foo(int n) {
    Obj obj;
    if (42 == n ) {
        throw "exception is thrown";
    }
}

TEST_CASE("Testing Modern CPP 001") {
    foo(41);
    foo(42);
}

// c++ 删除空指针，不会报错
TEST_CASE("Testing Modern CPP 002") {
    int* ptr = nullptr;
    delete ptr;
}

//实现智能指针
/**
 * v1
 *
template <typename T>
class smart_ptr {
public:
    explicit smart_ptr(T* ptr = nullptr)
        : ptr_(ptr) {}

    ~smart_ptr() { delete ptr_; }

    smart_ptr(smart_ptr& other) {
        ptr_ = other.release();
    }

    smart_ptr& operator=(smart_ptr& other) {
        smart_ptr(other).swap(*this);
        return *this;
    }

    T* release() {
        T* tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    }

    void swap(smart_ptr& other) {
        std::swap(ptr_, other.ptr_);
    }

    T* get() const { return ptr_; }

    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
    operator bool() const { return ptr_; }

private:
    T* ptr_;
};
 */

/**
 * v2，增加移动语义
 */
template <typename T>
class smart_ptr {
public:
    explicit smart_ptr(T* ptr = nullptr)
            : ptr_(ptr) {}

    ~smart_ptr() { delete ptr_; }

    // 使用移动语义，默认不会生成拷贝构造函数
    smart_ptr(smart_ptr&& other) {
        ptr_ = other.release();
    }

    smart_ptr& operator=(smart_ptr other) {
        other.swap(*this);
        return *this;
    }

    T* release() {
        T* tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    }

    void swap(smart_ptr& other) {
        std::swap(ptr_, other.ptr_);
    }

    T* get() const { return ptr_; }

    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
    operator bool() const { return ptr_; }

private:
    T* ptr_;
};

class shape {
public:
    virtual ~shape() {}
};

class circle : public shape {
public:
     ~circle() { puts("~circle"); }
};


TEST_CASE("Testing Modern CPP 003") {
    smart_ptr<shape> ptr1(new circle);
//    smart_ptr<shape> ptr2{ptr1}; // 重复释放指针
}

TEST_CASE("Testing Modern CPP 004") {
    smart_ptr<shape> ptr1(new circle);
//    smart_ptr<shape> ptr2{ptr1}; // 编译出错
    smart_ptr<shape> ptr3;
//    ptr3 = ptr1; // 编译出错
    ptr3 = std::move(ptr1);
    smart_ptr<shape> ptr4{std::move(ptr3)};

}

/**
* 测试左值，右值，移动语义等
*/

template <typename T>
void print_type() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

TEST_CASE("Testing Modern CPP 005") {
    int a = 10;
    double b = 3.14;
    int* c = &a;
    const int d = 10;

    int& ref = a;
    int&& rref = 30;
    print_type<decltype(a)>();
    print_type<decltype(b)>();
    print_type<decltype(c)>();
    print_type<decltype(d)>();
    print_type<decltype(ref)>();
    print_type<decltype(rref)>();

    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = std::move(v1);
    std::cout << v1.size() << std::endl;
    std::cout << v2.size() << std::endl;
    print_type<decltype(v1)>();
    print_type<decltype(v2)>();
}

/**
* 测试引用折叠
*/

// 目标函数，根据参数的值类别打印不同的消息
void target(int& x) {
    std::cout << "Target called with lvalue: " << x << std::endl;
}

void target(int&& x) {
    std::cout << "Target called with rvalue: " << x << std::endl;
}

// 包装函数，使用完美转发将参数传递给 target
template <typename T>
void wrapper(T&& arg) {
    print_type<decltype(arg)>();
    // 使用 std::forward 保留参数的值类别
    target(std::forward<T>(arg));
}

TEST_CASE("Testing Modern CPP 006") {
    int x = 10;

    // 传递左值
    wrapper(x); // T 推导为 int&，T&& 折叠为 int&，调用 target(int&)

    // 传递右值
    wrapper(20); // T 推导为 int，T&& 保持为 int&&，调用 target(int&&)

    // 传递右值（通过 std::move）
    wrapper(std::move(x)); // T 推导为 int，T&& 保持为 int&&，调用 target(int&&)

}

/**
* 测试vector
*/

class Obj1 {
public:
    Obj1() {
        std::printf("Obj1()\n");
    }

    Obj1(const Obj1& other) {
        std::printf("Obj1(const Obj1& other)\n");
    }

    Obj1(Obj1&& other) {
        std::printf("Obj1(Obj1&& other)\n");
    }
};

class Obj2 {
public:
    Obj2() {
        std::printf("Obj2()\n");
    }

    Obj2(const Obj2& other) {
        std::printf("Obj2(const Obj2& other)\n");
    }

    Obj2(Obj2&& other) noexcept {
        std::printf("Obj2(Obj2&& other)\n");
    }
};

TEST_CASE("Testing Modern CPP 007") {
    std::vector<Obj1> v1;
//    v1.resize(2);
//    v1.emplace_back();
//    v1.emplace_back();
    v1.reserve(2);
    v1.emplace_back();
    v1.emplace_back();
    v1.emplace_back(); // 设计vector的扩容，扩容时需要copy

    std::vector<Obj2> v2;
    v2.reserve(2);
    v2.emplace_back();
    v2.emplace_back();
//    v2.emplace_back();
}

/**
* 测试exception
*/

void foo1() {
    throw std::runtime_error("runtime error");
}

TEST_CASE("Testing Modern CPP 008") {
    try {
        foo1();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

//////////////////////////////////////////////////////////////
/**
 * @book 现代 C++ 教程
 * @link https://changkun.de/modern-cpp/
 */

/**
* chap-2 2.1.1 常量
*/

void foo_2_1(int i) {
    std::cout << "foo(int) is called" << std::endl;
}

void foo_2_1(char* str) {
    std::cout << "foo(char*) is called" << std::endl;
}

TEST_CASE("Testing Modern CPP 2.1.1") {
    if (std::is_same_v<decltype(NULL), decltype(0)>) {
        std::cout << "NULL is 0" << std::endl;
    }

    if (std::is_same_v<decltype(NULL), decltype((void*)0)>) {
        std::cout << "NULL is (void*)0" << std::endl;
    }

    if (std::is_same_v<decltype(NULL), decltype(nullptr)>) {
        std::cout << "NULL is nullptr" << std::endl;
    }

    foo_2_1(0);
    foo_2_1(nullptr);
}

/**
* chap-2 2.1.2 测试constexpr常量表达式和const常量的区别
*/
#define LEN 10

int len_foo() {
    int i = 2;
    return i;
}

constexpr int len_foo_constexpr() {
    int i = 5;
    return i;
}

constexpr int fib(int n) {
    if (n < 2) {
        return 1;
    }
    return fib(n - 1) + fib(n - 2);
}

TEST_CASE("Testing Modern CPP 2.1.2") {
    char arr_1[10];
    char arr_2[LEN];

    int len = 10;
    char arr_3[len]; // ?

    const int len_2 = len + 1;
    constexpr int len_2_constexpr = 1 + 2 + 2;
    char arr_4[len_2]; // ?
    char arr_5[len_2_constexpr];

    char arr_6[len_foo() + 5]; // ?

    char arr_7[len_foo_constexpr() + 5];

    std::cout << fib(10) << std::endl;

    int size = 10;
    int arr_8[size];
}

/**
* chap-2 2.2.1 测试if/switch变量声明强化
*/

TEST_CASE("Testing Modern CPP 2.2.1")  {
    std::vector<int> v = {1, 2, 3, 4};
    if (auto it = std::find(v.begin(), v.end(), 3); it != v.end()) {
        *it = 666;
    }
    for (auto& e : v) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

/**
* chap-2 2.2.2 测试初始化列表
*/

class MagicFoo {
public:
    MagicFoo(std::initializer_list<int> il) {
        for (auto it = il.begin(); it != il.end(); ++it) {
            vec_.push_back(*it);
        }
    }

public:
    std::vector<int> vec_;
};

TEST_CASE("Testing Modern CPP 2.2.2")  {
    MagicFoo mf = {1, 2, 3, 4};
    for (auto& e : mf.vec_) {
        std::cout << e << " ";
    };
}

/**
* chap-2 2.2.3 测试结构化绑定
*/

auto foo_2_2_3() {
    return std::make_tuple(1, 2.3, "hello");
}

TEST_CASE("Testing Modern CPP 2.2.3") {
    auto [x, y, z] = foo_2_2_3();
    std::cout << x << " " << y << " " << z << std::endl;
}

/**
 * chap-2 2.3 测试类型推导
 */

template<typename R , typename T, typename U>
R add(T x, U y) {
    return x + y;
}

template<typename T, typename U>
auto add2(T x, U y)-> decltype(x + y) {
    return x + y;
}


template<typename T, typename U>
auto add3(T x, U y) {
    return x + y;
}
TEST_CASE("Testing Modern CPP 2.3") {
    int x = add<int, int>(1, 2);
    double y = add<double, int>(1.1, 2.1);
}

/**
* chap-2 2.4 测试if constexpr
*/

template<typename T>
auto print_type_info(const T& x) {
    if constexpr (std::is_integral_v<T>) {
        return x + 1;
    } else {
        return x + 0.1;
    }
}
TEST_CASE("Testing Modern CPP 2.4")  {
    std::cout << print_type_info(1) << std::endl;
    std::cout << print_type_info(1.1) << std::endl;
}

/**
* chap-2 2.5.3 测试using和typdef的区别
*/

template<typename T>
class MagicType {
public:
  T x;
};

template<typename T>
using MagicTypeInt = MagicType<T>;

//template<typename T>
//typename MagicType<T> MagicTypeInt;

TEST_CASE("Testing Modern CPP 2.5.3")  {

   MagicTypeInt<int> mt;
}

///////////////////////////////////////////////////////////////
/**
 * chap-2 2.5.4 测试变参模板
 */
TEST_CASE("Testing HOPL4 str")  {
    const char* str1 = "hello";
    std::cout << "addr str1:" << (void*)str1 << std::endl;
    std::cout << "addr hello: " << &"hello" << std::endl;
    std::string str2{"hello"};
    std::cout << "addr str2:" << &str2 << std::endl;
    std::cout << "addr str2.c_str(): "<< (void*)str2.c_str() << std::endl;

}
template<typename T, typename... Args>
void printf(const char* s, const T& value, const Args&... args)
{
    while (*s) {
        if (*s == '%' && *++s != '%') {
            std::cout << value;
            if constexpr (sizeof...(args) > 0) {
                printf(++s, args...);  // 递归调用
            } else {
                ++s;  // 跳过占位符
            }
            return;
        }
        std::cout << *s++;
    }
    if constexpr (sizeof...(args) > 0) {
        throw std::runtime_error("extra arguments provided to printf");
    }
}

// 递归模板函数
template<typename T0>
void printf1(T0 value) {
    std::cout << value << std::endl;
}

template<typename T, typename... Args>
void printf1(T value, Args... args) {
    std::cout << value << std::endl;
    printf1(args...);
}

// 变参模板展开

template<typename T, typename... Args>
void printf2(T value, Args...args) {
    std::cout << value << std::endl;
    if constexpr (sizeof...(args) > 0) {
        printf2(args...);
    }
}

TEST_CASE("Testing HOPL4 printf")  {
//    printf("hello %d %s %f", 1, "world", 3.14);
    printf1(1, 2, "123", 1.23);
    printf2(1, 2, "123", 1.23);
}

/**
 * chap-2 2.5.5 测试折叠表达式
 */

template<typename... Args>
auto sum(Args... args) {
    return (args + ...);
}

//#include <iostream>
//using namespace std;
//
//template<typename ... Args>
//auto sum(Args... args)
//{
//    return (args + ...);
//}
//
//#ifdef INSIGHTS_USE_TEMPLATE
//template<>
//int sum<int, int, int, int, int>(int __args0, int __args1, int __args2, int __args3, int __args4)
//{
//  return __args0 + (__args1 + (__args2 + (__args3 + __args4)));
//}
//#endif
//
//
//int main()
//{
//    std::cout.operator<<(sum(1, 2, 3, 4, 5)).operator<<(std::endl);
//    return 0;
//}


TEST_CASE("Testing Modern CPP 2.5.5")  {

    std::cout << sum(1, 2, 3, 4, 5) << std::endl;
}

/**
 * chap-2 2.5.6 测试非类型模板参数
 */
template<auto value>
void foo_2_5_6() {
    std::cout << value << std::endl;
}

TEST_CASE("Testing Modern CPP 2.5.6")  {
    foo_2_5_6<100>();
}

/**
* 2.6.1 测试强枚举类型
*/

enum class Status : int {
    OK = 0,
    ERROR = 1,
};

// C++ 17
template<typename T>
std::ostream& operator<<(std::ostream& stream, const T& e) {
    if constexpr (std::is_enum_v<T>) {
        return stream << static_cast<std::underlying_type_t<T>>(e);
    } else {
        static_assert(false, "T must be an enum type!");
    }
}

TEST_CASE("Testing Modern CPP 2.6.1")  {
    std::cout << Status::OK << std::endl;
    std::cout << static_cast<int>(Status::OK) << std::endl;
}