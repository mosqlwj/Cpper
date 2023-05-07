//
// Created by lwj on 23-5-1.
//
#include "python_vm/code/BinaryFileParser.h"
#include <iostream>
#include <cassert>

namespace pvm {

    BinaryFileParser::BinaryFileParser(BufferedInputStream *stream) {
        m_file_stream = stream;
    }

    CodeObject *BinaryFileParser::Parse() {
        int magic_number = m_file_stream->ReadInt();
        printf("magic number is: 0x %x\n", magic_number);

        int moddate = m_file_stream->ReadInt();
        printf("moddate is: 0x %x\n", moddate);

        char object_type = m_file_stream->Read();
        if (object_type == 'c') {
            CodeObject* co = GetCodeObject();
            printf("parse OK\n");
            return co;
        }
        return nullptr;
    }

    CodeObject *BinaryFileParser::GetCodeObject() {
        int argcount = m_file_stream->ReadInt();
        std::cout << "argcount: " << argcount << std::endl;
        int nlocals = m_file_stream->ReadInt();
        std::cout << "nlocals: " << nlocals << std::endl;
        int stacksize = m_file_stream->ReadInt();
        std::cout << "stacksize: " << stacksize << std::endl;
        int flag = m_file_stream->ReadInt();
        std::cout << "flag: " << flag << std::endl;

        auto byte_code = GetByteCodes();
        std::cout << "byte code: " << byte_code->Value() << std::endl;
        auto consts = GetConsts();
        auto names = GetNames();
        auto var_name = GetVarNames();
        auto free_vars = GetFreeVars();
        auto cell_vars = GetCellVars();
        auto file_name = GetFileName();
        std::cout << "file name: " << file_name->Value() << std::endl;
        auto module_name = GetName();
        std::cout << "module name: " << module_name->Value() << std::endl;
        int lineno = m_file_stream->ReadInt();
        std::cout << "first line no: " << lineno << std::endl;
        auto lnotab = GetNoTable();

        return new CodeObject(argcount,
                              nlocals,
                              stacksize,
                              flag,
                              byte_code,
                              consts,
                              names,
                              var_name,
                              free_vars,
                              cell_vars,
                              file_name,
                              module_name,
                              lineno,
                              lnotab);
    }

    HiString *BinaryFileParser::GetByteCodes() {
        assert(m_file_stream->Read() == 's');
        return GetString();
    }

    HiString *BinaryFileParser::GetString() {
        int length = m_file_stream->ReadInt();
        char* str_val = new char [length];

        for (int i = 0; i < length; i++) {
            str_val[i] = m_file_stream->Read();
        }

        HiString* s = new HiString(str_val, length);
        delete[] str_val;
        return s;
    }

    ArrayList<HiObject *> *BinaryFileParser::GetConsts() {
        if (m_file_stream->Read() == '(') {
            return GetTuple();
        }
        m_file_stream->UnRead();
        return nullptr;
    }

    ArrayList<HiObject *> *BinaryFileParser::GetTuple() {
        int length = m_file_stream->ReadInt();
        HiString* str;
        auto list = new ArrayList<HiObject*>(length);
        for (int i = 0; i < length; i++) {
            char obj_type = m_file_stream->Read();
            switch (obj_type) {
                case 'c':
                    std::cout << "got a code object" << std::endl;
                    list->Add(GetCodeObject());
                    break;
                case 'i':
                    list->Add(new HiInteger(m_file_stream->ReadInt()));
                    break ;
                case 'N':
                    list->Add(nullptr);
                    break ;

                case 't':
                    str = GetString();
                    list->Add(str);
                    m_string_table.Add(str);
                    break ;

                case 's':
                    list->Add(GetString());
                    break ;

                case 'R':
                    list->Add(m_string_table.Get(m_file_stream->ReadInt()));
                    break ;

                default:
                    std::cout << "wrong object" << std::endl;
                    break ;
            }
        }
        return list;
    }

    HiString *BinaryFileParser::GetNoTable() {
        char ch = m_file_stream->Read();
        if (ch != 's' && ch != 't') {
            m_file_stream->UnRead();
            return nullptr;
        }
        return GetString();
    }

    HiString *BinaryFileParser::GetName() {
        char ch = m_file_stream->Read();

        if (ch == 's') {
            return GetString();
        }
        else if (ch == 't') {
            HiString* str = GetString();
            m_string_table.Add(str);
            return str;
        }
        else if (ch == 'R') {
            return m_string_table.Get(m_file_stream->ReadInt());
        }

        return nullptr;
    }

    int BinaryFileParser::GetInt() {
            return 0;
    }

    HiString *BinaryFileParser::GetFileName() {
        return GetName();
    }

    ArrayList<HiObject *> *BinaryFileParser::GetNames() {
        if (m_file_stream->Read() == '(') {
            return GetTuple();
        }
        m_file_stream->UnRead();
        return nullptr;
    }

    ArrayList<HiObject *> *BinaryFileParser::GetVarNames() {
        if (m_file_stream->Read() == '(') {
            return GetTuple();
        }
        m_file_stream->UnRead();
        return nullptr;
    }

    ArrayList<HiObject *> *BinaryFileParser::GetCellVars() {
        if (m_file_stream->Read() == '(') {
            return GetTuple();
        }
        m_file_stream->UnRead();
        return nullptr;
    }

    ArrayList<HiObject *> *BinaryFileParser::GetFreeVars() {
        if (m_file_stream->Read() == '(') {
            return GetTuple();
        }
        m_file_stream->UnRead();
        return nullptr;
    }
}