//
// Created by liwenjie on 2024/6/3.
//
/*
 * @description: flatten model
 */
#ifndef NDB_FLAT_MODEL_H
#define NDB_FLAT_MODEL_H

#include "object.h"
#include "primitive.h"
#include <vector>
#include <unordered_map>
#include <cassert>


namespace ndb {
    class Primitive;


    class FlatModel : public Object {
    public:
        FlatModel(const std::string& name) : Object(name) {}

        bool IsFlatModel() override { return true; }

        void AddPrimitive(Primitive* primitive) {
            assert(primitive);
            flat_model_.push_back(primitive);
            name_to_primitive_[primitive->GetName()] = primitive;
        }
        auto GetPrimitives() { return flat_model_; }

        Primitive* GetPrimitiveByName(const std::string& name) {
            auto it = name_to_primitive_.find(name);
            if (it != name_to_primitive_.end()) {
                return it->second;
            }
            return nullptr;
        }
        // sort
    private:
        std::vector<Primitive*> flat_model_;
        std::unordered_map<std::string, Primitive*> name_to_primitive_;
    };
}
#endif//NDB_FLAT_MODEL_H
