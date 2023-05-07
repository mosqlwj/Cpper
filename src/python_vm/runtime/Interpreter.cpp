//
// Created by lwj on 23-5-7.
//
#include "python_vm/runtime/Interpreter.h"
#include "python_vm/object/HiInteger.h"
#include <cstdio>
namespace pvm {
    void Interpreter::Run(pvm::CodeObject *codes) {
        int pc = 0;
        int code_length = codes->m_bytecodes->Length();
        m_stacks = new ArrayList<HiObject*>(codes->m_stack_size);
        m_consts = codes->m_consts;

        while (pc < code_length) {
            unsigned char op_code = codes->m_bytecodes->Value()[pc++];
            bool has_argument = (op_code & 0xFF) >= ByteCode::HAVE_ARGUMENT;

            int op_arg = -1;
            if (has_argument) {
                int byte1 = (codes->m_bytecodes->Value()[pc++] & 0xFF);
                op_arg = ((codes->m_bytecodes->Value()[pc++] & 0xFF) << 8) | byte1;
            }

            HiObject* lhs, *rhs;
            HiObject* v, * w, * u, * attr;
            switch (op_code) {
                case ByteCode::LOAD_CONST:
                    m_stacks->Add(m_consts->Get(op_arg));
                    break ;
                case ByteCode::PRINT_ITEM:
                    v = m_stacks->Pop();
                    v->Print();
                    break ;

                case ByteCode::PRINT_NEWLINE:
                    printf("\n");
                    break ;

                case ByteCode::BINARY_ADD:
                    v = m_stacks->Pop();
                    w = m_stacks->Pop();
                    m_stacks->Add(w->Add(v));
                    break ;
                case ByteCode::RETURN_VALUE:
                    m_stacks->Pop();
                    break ;

                default:
                    printf("Error: wrong byte code %d \n", op_code);
            }
        }
    }
}