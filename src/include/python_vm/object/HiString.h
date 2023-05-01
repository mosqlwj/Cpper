#ifndef HI_STRING
#define HI_STRING

#include "HiObject.h"
#include <cstring>

namespace pvm {

class HiString : public HiObject{
public:
    HiString(const char* x) {
        m_length = strlen(x);
        m_value = new char[m_length];
        strcpy(m_value, x);
    }

    HiString(const char* x, int length) {
        m_length = length;
        m_value = new char[m_length];
        for (int i = 0; i < length; i++) {
            m_value[i] = x[i];
        }
    }

    const char* Value() { return m_value; }
    int Length() { return m_length; }
private:
    char* m_value{ nullptr};
    int m_length;
};
}
#endif