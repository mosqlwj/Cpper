//
// Created by liwenjie on 2024/5/30.
//

#ifndef CPPER_LIBRARY_H
#define CPPER_LIBRARY_H

#include "object.h"
#include "module.h"

#include <vector>
#include <hash_map>



//class Module;
namespace ndb {
    struct DftCellSelection {

    };

    class Library : public Object {
    public:
        explicit Library(const std::string& name = "work") : Object(name) {}

        void AddModule(Module* module) {
            assert(module);
            modules_.push_back(module);
            name_map_[module->GetName()] = module;
        }

        auto GetModules() const {
            return modules_;
        }

        Module* GetModuleByName(const std::string& name) const {
            auto it = name_map_.find(name);
            if (it != name_map_.end()) {
                return it->second;
            }
            return nullptr;
        }

        bool IsLibrary() override {
            return true;
        }
    private:
        // basic attributes
        std::vector<Module*> modules_; // include module and LibCell
        std::unordered_map<std::string, Module*> name_map_;
    private:
        // dft attributes
    };

}
#endif//CPPER_LIBRARY_H
