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

    HiObject* Greater(HiObject* x) override {
        if (m_value > ((HiInteger*)x)->Value()) {
            return new HiInteger(1);
        } else {
            return new HiInteger(0);
        }
    }

    HiObject* Less(HiObject* x) override {
         if (m_value < ((HiInteger*)x)->Value()) {
            return new HiInteger(1);
        } else {
            return new HiInteger(0);
        }
    }

    HiObject* Equal(HiObject* x) override {
         if (m_value == ((HiInteger*)x)->Value()) {
            return new HiInteger(1);
        } else {
            return new HiInteger(0);
        }
    }
    HiObject* NotEqual(HiObject* x) override {
         if (m_value != ((HiInteger*)x)->Value()) {
            return new HiInteger(1);
        } else {
            return new HiInteger(0);
        }
    }
    HiObject* GreaterEqual(HiObject* x) override {
         if (m_value >= ((HiInteger*)x)->Value()) {
            return new HiInteger(1);
        } else {
            return new HiInteger(0);
        }
    }

    HiObject* LessEqual(HiObject* x) override {
         if (m_value <= ((HiInteger*)x)->Value()) {
            return new HiInteger(1);
        } else {
            return new HiInteger(0);
        }
    }


private:
    int m_value;
};
}
#endif