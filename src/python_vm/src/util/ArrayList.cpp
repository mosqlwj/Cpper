#include "python_vm/util/ArrayList.h"
#include <cstdio>

namespace pvm {

template<class T>
ArrayList<T>::ArrayList(int n) {
    m_length = n; // capacity
    m_size = 0; // 有效元素
    m_array = new T[n];
}

template<class T>
void ArrayList<T>::Add(T t) {

    if (m_size >= m_length) {
        Expand();
    }
    m_array[m_size++] = t;
}

template<class T>
void ArrayList<T>::Insert(int index, T t) {
//    Add(nullptr);
    for (int i = m_size - 1; i > index; i--) {
        m_array[i] = m_array[i - 1];
    }
    m_array[index] = t;
}

template<class T>
void ArrayList<T>::Expand() {
    T* new_array = new T[m_length << 1];
    for (int i = 0; i < m_length; i++) {
        new_array[i] = m_array[i];
    }
    delete[] m_array;
    m_array = new_array;
    m_length << 1;
    printf("expand array to %d, size is %d \n", m_length, m_size);
}

template<class T>
int ArrayList<T>::Size() {
    return m_size;
}

template<class T>
int ArrayList<T>::Length() {
    return m_length;
}

template<class T>
T ArrayList<T>::Get(int index) {
    return m_array[index];
}

template<class T>
void ArrayList<T>::Set(int index, T t) {
    // 索引大于有效元素个数
    if (m_size <= index) {
        m_size = index + 1;
    }

    while (m_size > m_length) {
        Expand();
    }

    m_array[index] = t;
}

template<class T>
T ArrayList<T>::Pop() {
    return m_array[--m_size];
}
}