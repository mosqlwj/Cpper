#ifndef OBJECT_H
#define OBJECT_H

#include <string>

namespace ndb {

class Object {

public:
    Object(const std::string& name) : name_(name) {}

    virtual unsigned IsNetlist()  { return 0; }
    
    
    virtual unsigned IsModule()   { return 0; }
    virtual unsigned IsInstance() { return 0; }
    
    virtual unsigned IsPort()     { return 0; }
    virtual unsigned IsNet()      { return 0; }
    virtual unsigned IsPin()      { return 0; }


private:
    std::string name_;
};
}

#endif

