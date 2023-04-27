//
// Created by liwenjie on 2023/3/10.
//
// foo.h
#ifdef __cplusplus
extern "C" {
#endif

int add(int x, int y);

#ifdef __cplusplus
}
#endif

// foo.c
int add(int x, int y) {
    return x + y;
}

// 1.1.cpp
//#include "foo.h"
#include <functional>
#include <iostream>

int main() {
    [out = std::ref(std::cout << "Result from C code: " << add(1, 2))]() {
        out.get() << ".\n";
    }();
    return 0;
}