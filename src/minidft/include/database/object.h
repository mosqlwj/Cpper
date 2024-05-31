#ifndef NDB_OBJECT_H
#define NDB_OBJECT_H

#include <string>

namespace ndb {

class Object {

public:
    Object(const std::string& name) : name_(name) {}

    const std::string& GetName() const { return name_; }

    virtual unsigned IsNetlist()  { return 0; }
    virtual unsigned IsLibrary()  { return 0; }
    
    virtual unsigned IsModule()   { return 0; }
    virtual unsigned IsInstance() { return 0; }
    virtual unsigned IsLibCell()  { return 0; }  // instance of library module
    virtual unsigned IsAssign()  { return 0; }
    
    virtual unsigned IsPort()     { return 0; }
    virtual unsigned IsNet()      { return 0; }
    virtual unsigned IsPin()      { return 0; }
    virtual unsigned IsPortBus()  { return 0; }
    virtual unsigned IsNetBus()   { return 0; }
    virtual unsigned IsPinBus()   { return 0; }

    virtual unsigned IsPrimitive() { return 0; }
    virtual unsigned IsGatePin() { return 0; }

private:
    std::string name_;
};
}

#endif

