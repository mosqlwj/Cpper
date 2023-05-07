#ifndef HI_INTEGER
#define HI_INTEGER

#include "HiObject.h"
#include <cstdio>

namespace pvm {

class HiInteger : public HiObject{
public:
    HiInteger(int t) : m_value(t) {}
    int Value() { return m_value; }

    void Print() override {
        printf(" %d", m_value);
    }
    HiObject * Add(pvm::HiObject *x) override {
        return new HiInteger(m_value + ((HiInteger*)x)->Value());
    }
private:
    int m_value;
};
}
#endif