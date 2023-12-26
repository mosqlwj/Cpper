//
// Created by lwj on 23-5-1.
//
#include "python_vm/code/BinaryFileParser.h"
#include "python_vm/runtime/Interpreter.h"
#include <string>

using namespace pvm;
int main(int argc, char* argv[]) {
//    if (argc <= 1) {
//        printf("vm need a parameter : filename\n");
//        return 0;
//    }

    BufferedInputStream stream("/home/lwj/workspace/pythonvm/test/test_if.pyc");
    BinaryFileParser parser(&stream);
    auto codes = parser.Parse();
    Interpreter interpreter;
    interpreter.Run(codes);

    return 0;
}