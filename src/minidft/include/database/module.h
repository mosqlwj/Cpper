//
// Created by liwenjie on 2024/6/3.
//

#ifndef NDB_MODULE_H
#define NDB_MODULE_H

#include <vector>
#include <unordered_map>

#include "object.h"

class Instance;
class Port;

namespace ndb {
    class Module : public Object {
    public:
        Module(const std::string& name) : Object(name)  {}

        bool IsModule() override { return true; }

        void AddPort() {}



    private:
        // basic attribute

        std::vector<Instance*> instances_;
        std::unordered_map<std::string, Instance*> name_to_instance_;
        std::vector<Port*> ports_;
        std::unordered_map<std::string, Port*> name_to_port_;

        // 黑盒设置
        bool is_black_box_ = false;


    private:
        // dft attribute
    };
}
#endif//NDB_MODULE_H