#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"



#include <vector>
#include <string>
#include <string_view>

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