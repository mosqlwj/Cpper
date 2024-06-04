//
// Created by liwenjie on 2024/5/30.
//

#ifndef CPPER_LIBRARY_H
#define CPPER_LIBRARY_H

#include <vector>
#include <hash_map>

#include "object.h"

class Module;
namespace ndb {
    struct DftCellSelection {

    };
    class Library : public Object {
    public:
        explicit Library(const std::string& name) : Object(name) {
            name_map_.clear();
        }
    private:
        // basic attributes
        std::vector<Module*> modules_;
        std::unordered_map<std::string, Module*> name_map_;
    private:
        // dft attributes
    };

}
#endif//CPPER_LIBRARY_H
