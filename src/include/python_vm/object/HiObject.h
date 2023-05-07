#ifndef HI_OBJECT
#define HI_OBJECT

namespace pvm {

class HiObject {
public:
    virtual void Print() {}
    virtual HiObject *Add(HiObject* x) {
        return nullptr;
    }
};
}
#endif