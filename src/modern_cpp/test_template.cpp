//
// Created by liwenjie on 2024/12/26.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>
// #include <format>
//////////////////////////////////////////
// 函数模板

template <typename T>
T max(T a, T b) {
    return a > b ? a : b;
}

struct Test {
    int v_;
    Test() = default;
    Test(int v) : v_(v) {}

    bool operator> (const Test& rhs) const {
        return v_ > rhs.v_;
    }
};
// TEST_CASE("Test Func Template 001")  {
//     int a{1};
//     int b{2};
//
//     std::cout << std::format("max:{}", ::max(a, b));
//
//     Test t1{10};
//     Test t2{20};
// //    std::printf("max:{}", ::max(t1, t2));
//     std::cout << std::format("max:{}", ::max(t1, t2).v_);
// }

// 变量模板偏特化

template<typename T>
const char* s = "?";

template<typename T>
const char* s<T*> = "pointer";

template<typename T>
const char* s<T[]> = "array";

TEST_CASE("Test Template 010")  {
    std::cout << s<int> << std::endl;
    std::cout << s<int*> << '\n';           // pointer
    std::cout << s<std::string*> << '\n';   // pointer
    std::cout << s<int[]> << '\n';          // array
    std::cout << s<double[]> << '\n';       // array
    std::cout << s<int[1]> << '\n';         // ?
}

////////////////////////////////////
template<typename T,typename T2>
const char* s1 = "?";

template<typename T2>
const char* s1<int, T2> = "T == int";

TEST_CASE("Test Template 011")  {
    std::cout << s1<char, double> << '\n';       // ?
    std::cout << s1<int, double> << '\n';        // T == int
    std::cout << s1<int, std::string> << '\n';   // T == int
}

//折叠表达式

template<typename...Args>
void print(const Args&...args) {
    (...,(std::cout << args << ' '));
}


TEST_CASE("Test Template 012")  {
    print("luse", 1, 1.2); // luse 1 1.2
}

template<int...I>
constexpr int v_right = (I - ...);  // 一元右折叠

template<int...I>
constexpr int v_left = (... - I);   // 一元左折叠



// template<>
// constexpr const int v_right<4, 5, 6> = 4 - (5 - 6);
//
// template<>
// constexpr const int v_left<4, 5, 6> = (4 - 5) - 6;


TEST_CASE("Test Template 013")  {
    std::cout << v_right<4, 5, 6> << '\n';  //(4-(5-6)) 5
    std::cout << v_left<4, 5, 6> << '\n';   //((4-5)-6) -7
}

// 二元折叠

// 二元右折叠
template<int...I>
constexpr int v = (I + ... + 10);    // 1 + (2 + (3 + (4 + 10)))
// 二元左折叠
template<int...I>
constexpr int v2 = (10 + ... + I);   // (((10 + 1) + 2) + 3) + 4



TEST_CASE("Test Template 014")  {
    std::cout << v<1, 2, 3, 4> << '\n';  // 20
    std::cout << v2<1, 2, 3, 4> << '\n'; // 20
}



// 待决名
//
// 墨盒模板
template<typename T>
class InkCartridge {
public:
    using ContentType = T;  // 嵌套类型

    // 成员模板函数
    template<int Size>
    void load() {
        std::cout << "加载" << Size << "ml " << typeid(T).name() << "墨水\n";
    }
};

// 打印机模板
template<typename Cartridge>
class Printer {
public:
    // 必须使用 typename 声明嵌套类型
    typename Cartridge::ContentType currentInk;

    void print() {
        std::cout << "使用 " << typeid(currentInk).name() << " 墨水打印\n";
    }

    // 必须使用 template 调用成员模板函数
    void replaceCartridge() {
        Cartridge newCart;
        newCart.template load<100>();  // 正确写法
        // newCart.load<100>();        // 错误写法：编译器无法识别模板
    }
};

TEST_CASE("Test Template 015") {
    Printer<InkCartridge<int>> colorPrinter;
    colorPrinter.replaceCartridge();
    colorPrinter.print();

    // 验证嵌套类型
    using MyCartridge = InkCartridge<double>;
    typename MyCartridge::ContentType ink = 3.14;  // 正确写法

}

// concept && require
