//
// Created by lwj on 23-5-1.
//
#include "python_vm/code/BinaryFileParser.h"

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

    }
}