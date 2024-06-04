#ifndef NDB_OBJECT_H
#define NDB_OBJECT_H

#include <string>

namespace ndb {

class Object {

public:
    explicit Object(const std::string& name) : name_(name) {}

    const std::string& GetName() const { return name_; }

    virtual bool IsNetlist()  { return false; }
    virtual bool IsLibrary()  { return false; }
    
    virtual bool IsModule()   { return false; }
    virtual bool IsInstance() { return false; }
    virtual bool IsLibCell()  { return false; }  // instance of library module
    virtual bool IsAssign()  { return false; }
    
    virtual bool IsPort()     { return false; }
    virtual bool IsNet()      { return false; }
    virtual bool IsPin()      { return false; }
    virtual bool IsPortBus()  { return false; }
    virtual bool IsNetBus()   { return false; }
    virtual bool IsPinBus()   { return false; }

    virtual bool IsPrimitive() { return false; }
    virtual bool IsGatePin() { return false; }

private:
    std::string name_;
};
}

#endif

