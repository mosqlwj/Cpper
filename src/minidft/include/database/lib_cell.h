//
// Created by liwenjie on 2024/6/3.
//

#ifndef NDB_LIB_CELL_H
#define NDB_LIB_CELL_H

#include "module.h"
#include "unordered_map"


namespace ndb {
    class Primitive;


    class LibCell : public Module {
    public:
        LibCell(const std::string& name) : Module(name) {}

        bool IsLibCell() override { return true; }

        void AddPrimitive(Primitive* primitive) { primitives_.push_back(primitive);}
        auto GetPrimitives() { return primitives_; }

        Primitive* GetPrimitiveByName(const std::string& name) {
            if (name_to_primitive_.find(name) != name_to_primitive_.end()) {
                return name_to_primitive_[name];
            }
            return nullptr;
        }
    private:
        std::vector<Primitive*> primitives_;
        std::unordered_map<std::string, Primitive*> name_to_primitive_;

    };
}
#endif//NDB_LIB_CELL_H
