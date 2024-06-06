//
// Created by liwenjie on 2024/6/3.
//

#ifndef NDB_MODULE_H
#define NDB_MODULE_H

#include <vector>
#include <unordered_map>
#include <cassert>

#include "object.h"

class Instance;
class Port;
class Net;
class Assign;

namespace ndb {
    class Module : public Object {
    public:
        Module(const std::string& name) : Object(name)  {}

        bool IsModule() override { return true; }

        void AddPort(Port* port) {
            assert(port);
            ports_.emplace_back(port);
        }
        auto GetPorts() const { return ports_; }
        auto GetPortByName(const std::string& name) { return name_to_port_[name]; }



    private:
        // basic attribute

        // include ports
        std::vector<Port*> ports_;
        std::unordered_map<std::string, Port*> name_to_port_;

        // include nets
        std::vector<Net*> nets_;
        std::unordered_map<std::string, Net*> name_to_net_;

        // include assign
        std::vector<Assign*> assigns_;

        // include instance
        std::vector<Instance*> instances_;
        std::unordered_map<std::string, Instance*> name_to_instance_;

        // black box setting
        bool is_black_box_ = false;


    private:
        // dft attribute
    };
}
#endif//NDB_MODULE_H