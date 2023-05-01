#ifndef HI_INTEGER
#define HI_INTEGER

#include "HiObject.h"


namespace pvm {

class HiInteger : public HiObject{
public:
    HiInteger(int t) : m_value(t) {}
    int Value() { return m_value; }
private:
    int m_value;
};
}
#endif