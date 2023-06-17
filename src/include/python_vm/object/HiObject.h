#ifndef HI_OBJECT
#define HI_OBJECT

namespace pvm {

class HiObject {
public:
    virtual void Print() {}
    virtual HiObject* Add(HiObject* x) {
        return nullptr;
    }

    virtual HiObject* Greater(HiObject* x) {
        return nullptr;
    }
    virtual HiObject* Less(HiObject* x) {
        return nullptr;
    }
    virtual HiObject* Equal(HiObject* x) {
        return nullptr;
    }
    virtual HiObject* NotEqual(HiObject* x) {
        return nullptr;
    }
    virtual HiObject* GreaterEqual(HiObject* x) {
        return nullptr;
    }
    virtual HiObject* LessEqual(HiObject* x) {
        return nullptr;
    }
};
}
#endif