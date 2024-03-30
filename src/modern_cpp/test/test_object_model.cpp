//
// Created by liwenjie on 2024/3/30.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

//Base
#include <iostream>

using namespace std;
class Base {
public:
    Base(int);
    virtual ~Base(void);

    int getIBase() const;
    static int instanceCount();
    virtual void print() const;

protected:

    int iBase;
    static int count;
};

TEST_CASE("Test Case01") {
    Base b(10);
    b.print();
    std::cout << "Test Case01" << std::endl;
}