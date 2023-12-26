//
// Created by lwj on 23-5-1.
//
#include "python_vm/util/ArrayList.h"

#include <iostream>

int main() {

    pvm::ArrayList<int> arr;
    arr.Add(1);
    arr.Add(2);
    arr.Add(3);
    std::cout << arr.Length() << " , " << arr.Size() << std::endl;
    std::cout << arr.Get(2) << std::endl;
    int ret = arr.Pop();
    std::cout << ret << std::endl;
    std::cout << arr.Length() << " , " << arr.Size() << std::endl;
    return 0;
}