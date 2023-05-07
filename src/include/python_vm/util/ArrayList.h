#ifndef ARRAY_LIST
#define ARRAY_LIST
namespace pvm {

template <class T> 
class ArrayList {

public:
    ArrayList(int n = 8);

    void Add(T t);
    void Insert(int index, T t);
    T Get(int index);
    void Set(int index, T t);
    int Size();
    int Length();
    T Pop();
private:
    void Expand();
private:
    int m_length;
    T*  m_array;
    int m_size;

};

// 模板必须先实例化，才能.h和.cpp文件分离
template class ArrayList<int>;


class HiObject;
template class ArrayList<HiObject*>;

class HiString;
template class ArrayList<HiString*>;
}

#endif