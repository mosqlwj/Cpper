//
// Created by lwj on 23-5-1.
//
#include "python_vm/object/HiString.h"

#include <iostream>
int main() {

    pvm::HiString str("hello");
    std::cout << str.Value() << " , " << str.Length() << std::endl;
    return 0;
}