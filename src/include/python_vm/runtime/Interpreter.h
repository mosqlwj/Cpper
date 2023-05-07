//
// Created by lwj on 23-5-7.
//

#ifndef MORDERN_CPP_INTERPRETER_H
#define MORDERN_CPP_INTERPRETER_H

#include "python_vm/object/HiObject.h"
#include "python_vm/util/ArrayList.h"
#include "python_vm/code/CodeObject.h"
#include "python_vm/code/ByteCode.h"

namespace pvm {
    class Interpreter {
    public:
        void Run(CodeObject* codes);
    private:
        ArrayList<HiObject*>* m_stacks;
        ArrayList<HiObject*>* m_consts;
    };
}

#endif//MORDERN_CPP_INTERPRETER_H
