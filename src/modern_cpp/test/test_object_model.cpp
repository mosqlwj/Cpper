//
// Created by liwenjie on 2024/3/30.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>

class WithAlign {
    int a;
    char b;
};

#pragma pack(push, 1)
class WithoutAlign {
    int a;
    char b;
};
#pragma pack(pop)

TEST_CASE("Test align") {
    WithAlign w;
    WithoutAlign wo;
    std::cout << "WithAlign size: " << sizeof(w) << std::endl;
    std::cout << "WithoutAlign size: " << sizeof(wo) << std::endl;
    CHECK(sizeof(WithAlign) == 8);
    CHECK(sizeof(WithoutAlign) == 5);
}


#pragma pack(push, 1)
class Base {
public:
    Base(int d) : data_(d) { ++instance_cnt_; }                            // constructor, non-static function
    virtual ~Base() { std::cout << "destructor: " << this << std::endl; }  // destructor, virtual function
    static int getInstanceCnt() { return instance_cnt_; }                  // static function
    int getData() { return data_; }                                        // non-static function
    virtual void print() {                                                 // virtual function
        std::cout << "[Base] address: " << this << " data: " << this->data_ << std::endl;
    }

public:
    int data_;                 // non-static data
    static int instance_cnt_;  // static data
};

int Base::instance_cnt_ = 0;
#pragma pack(pop)

TEST_CASE("Test Base"){
    Base *a = new Base(100);
    Base *b = new Base(200);

    uint64_t ptr_list[2] = {(uint64_t)a, (uint64_t)b};

    for (int idx = 0; idx < 2; ++idx) {
        uint64_t ptr = ptr_list[idx];
        std::cout << "instance " << idx << " address " << (void *)ptr << std::endl;

        uint64_t pointer2vptr = ptr;                // 指向vptr的地址，前8字节存放vptr
        uint64_t pointer2data = ptr + 8;            // 指向数据的地址，之后存放数据
        uint64_t vptr = *(uint64_t *)pointer2vptr;  // 获取vptr的具体数据
        int data = *(int *)pointer2data;            // 获取data的具体数据

        std::cout << "  vptr address " << (void *)pointer2vptr << " vptr " << (void *)vptr << std::endl;
        std::cout << "  data address " << (void *)pointer2data << " data " << data << std::endl;

        // 关于虚表
        // 1. 虚表存放了多个指针，顺序是：offset, type_info, virtual_func1, virtual_func2, ...
        // 2. 虚函数在虚表中的顺序和声明的顺序一致
        // 3. 实例的vptr指向的是第一个virtual_func，而不是vtable真正的起点
        // 4. GCC对于虚析构函数会生成两个虚函数
        uint64_t *vtable = (uint64_t *)vptr;  // 严格来说是 vptr - 16
        uint64_t offset_ptr = vtable[-2];
        uint64_t type_info_ptr = vtable[-1];
        uint64_t destructor1_ptr = vtable[0];  // 析构函数，但是不调用delete()
        uint64_t destructor2_ptr = vtable[1];  // 析构函数，析构完调用delete()
        uint64_t print_fn_ptr = vtable[2];

        std::cout << "vtable address " << vtable << std::endl;
        std::cout << "  offset address " << (void *)offset_ptr << std::endl;
        std::cout << "  type_info address " << (void *)type_info_ptr << std::endl;
        std::cout << "  destructor1 address " << (void *)destructor1_ptr << std::endl;
        std::cout << "  destructor2 address " << (void *)destructor2_ptr << std::endl;
        std::cout << "  print_fn address " << (void *)print_fn_ptr << std::endl;

        typedef void (*print_fn_type)(void *);  // print函数的类型，入参是一个指针，且无返回值

        // call print
        std::cout << "call from instance:" << std::endl;
        ((Base *)ptr)->print();
        std::cout << "call from vtable:" << std::endl;
        ((print_fn_type)print_fn_ptr)((void *)ptr);

        typedef void (*del_fn)(void *);
        ((del_fn)(destructor2_ptr))((void *)ptr);  // 这里调用第二个析构函数

        std::cout << std::endl;
    }
}

#pragma pack(push, 1)
class A {
public:
    A(int d) : data_(d) {}                                                  // constructor, non-static function
    virtual ~A() { std::cout << "[A] destructor: " << this << std::endl; }  // destructor, virtual function
    virtual void print() {                                                  // virtual function
        std::cout << "[A] address: " << this << " a: " << &this->data_ << " " << this->data_ << std::endl;
    }

public:
    int data_;  // non-static data
};

class B : public A {
public:
    B(int a, int b) : A(a), data_(b) {}
    virtual ~B() { std::cout << "[B] destructor: " << this << std::endl; }
    virtual void printB() {
        std::cout << "[B] address: " << this                             // this
                  << " a: " << &this->A::data_ << " " << this->A::data_  // A
                  << " b: " << &this->data_ << " " << this->data_        // B
                  << std::endl;
    }

public:
    int data_;
};

class C : public B {
public:
    C(int a, int b, int c) : B(a, b), data_(c) {}
    virtual ~C() { std::cout << "[C] destructor: " << this << std::endl; }
    virtual void print() {
        std::cout << "[C] address: " << this  // this
                  << " a: " << &this->A::data_ << " " << this->A::data_ << " " << &this->B::A::data_ << " "
                  << this->B::A::data_                                   // A
                  << " b: " << &this->B::data_ << " " << this->B::data_  // B
                  << " c: " << &this->data_ << " " << this->data_        // C
                  << std::endl;
    }

public:
    int data_;
};

#pragma pack(pop)

TEST_CASE("Test A_B_C inheritance") {
    std::cout << "Sizeof: A " << sizeof(A) << " B " << sizeof(B) << " C " << sizeof(C) << std::endl;

    A *a = new A(100);
    A *b = new B(200, 300);
    A *c = new C(400, 500, 600);

    a->print();          // A::print
    b->print();          // A:print
    ((B *)b)->printB();  // B:printB
    c->print();          // C:print
    ((B *)c)->printB();  // B:printB

    delete a;
    delete b;
    delete c;
}