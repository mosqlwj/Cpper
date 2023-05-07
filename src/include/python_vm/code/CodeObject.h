#ifndef CODE_OBJECT
#define CODE_OBJECT

#include "python_vm/object/HiObject.h"
#include "python_vm/object/HiString.h"
namespace pvm {

//class HiString;
template <class T>
class ArrayList;

class CodeObject : public HiObject{
public:
    int m_argcount;
    int m_nlocals;
    int m_stack_size;
    int m_flag;

    HiString* m_bytecodes;
    ArrayList<HiObject*>* m_names;
    ArrayList<HiObject*>* m_consts;
    ArrayList<HiObject*>* m_var_names;

    ArrayList<HiObject*>* m_free_vars;
    ArrayList<HiObject*>* m_cell_vars;

    HiString* m_co_name;
    HiString* m_file_name;

    int m_lineno;
    HiString* m_notable;

    CodeObject(int argcount,
               int nlocals,
               int stacksize,
               int flag,
               HiString* bytecodes,
               ArrayList<HiObject*>* consts,
               ArrayList<HiObject*>* names,
               ArrayList<HiObject*>* varnames,
               ArrayList<HiObject*>* freevars,
               ArrayList<HiObject*>* cellvars,
               HiString* file_name,
               HiString* co_name,
               int lineno,
               HiString* notable)
        : m_argcount(argcount),
          m_nlocals(nlocals),
          m_stack_size(stacksize),
          m_flag(flag),
          m_bytecodes(bytecodes),
          m_names(names),
          m_consts(consts),
          m_var_names(varnames),
          m_free_vars(freevars),
          m_cell_vars(cellvars),
          m_co_name(co_name),
          m_file_name(file_name),
          m_lineno(lineno),
          m_notable(notable) {}


};

}
#endif