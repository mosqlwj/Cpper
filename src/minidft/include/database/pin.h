#ifndef NDB_PIN_H
#define NDB_PIN_H

#include "object.h"

class Instance;
namespace ndb {

    class Pin : public Object{

    public:
    private:
        int32_t pin_index_;
        Instance* of_instance_;

        //
    };
}

#endif