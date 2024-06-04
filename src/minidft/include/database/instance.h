//
// Created by liwenjie on 2024/6/3.
//

#ifndef NDB_INSTANCE_H
#define NDB_INSTANCE_H

#include <vector>

#include "object.h"

class Module;
class Pin;
namespace ndb {

    class Instance : public Object {
    public:
        /*
         *
         */
        Instance(const std::string& name, Module* ref_module) :
                                                                Object(name),
                                                                ref_module_(ref_module) {
            parent_ = nullptr;
        }
        bool IsInstance() override { return true; }

        std::string GetFullName() { return ""; }  // hierarchy name, "U1/I1"
        std::string GetBaseName() { return ""; }  // base name, "U1"
        std::string GetLeafName() { return ""; }  // leaf name, "I1"

        void GetParent() {}
        void GetRefModule() {}
        void GetPins() {}


        void Link(Module*) {}


    private:
        // basic attributes
        std::string base_name_;
        std::string leaf_name_;

        Instance* parent_;
        Module* ref_module_;
        std::vector<Pin*> pins_;

    private:
        // dft attributes
    };
}
#endif//NDB_INSTANCE_H