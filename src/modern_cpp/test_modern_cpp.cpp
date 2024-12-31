#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"



#include <vector>
#include <string>
#include <string_view>
#include <iostream>
#include <utility> // for std::forward

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