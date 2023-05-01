#ifndef BINARY_FILE_OBJECT
#define BINARY_FILE_OBJECT

#include "python_vm/object/HiObject.h"
#include "python_vm/object/HiInteger.h"
#include "python_vm/object/HiString.h"
#include "python_vm/util/ArrayList.h"
#include "python_vm/util/BufferedInputStream.h"
#include "python_vm/code/CodeObject.h"

namespace pvm {

class BinaryFileParser{

public:
    BinaryFileParser(BufferedInputStream* stream);

public:
    CodeObject* Parse();
    CodeObject* GetCodeObject();
    HiString*   GetByteCodes();
    HiString*   GetNoTable();
    int         GetInt();
    HiString*   GetString();
    HiString*   GetName();

    HiString*   GetFileName();

    ArrayList<HiObject*>*   GetConsts();
    ArrayList<HiObject*>*   GetNames();
    ArrayList<HiObject*>*   GetVarNames();
    ArrayList<HiObject*>*   GetFreeVars();
    ArrayList<HiObject*>*   GetCellVars();
    ArrayList<HiObject*>*   GetTuple();
private:
    BufferedInputStream* m_file_stream;
    int m_curr;
    ArrayList<HiString*> m_string_table;
};
}
#endif