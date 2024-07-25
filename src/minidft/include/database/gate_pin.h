//
// Created by liwenjie on 2024/6/3.
//
/*
 * @description: for flatten model
 */
#ifndef NDB_GATE_PIN_H
#define NDB_GATE_PIN_H

#include "object.h"
#include "define.h"
#include <cassert>

namespace ndb {
    class Primitive;

    class GatePin : public Object {
    public:
        GatePin(const std::string& name, Direction dir) : Object(name), dir_(dir) {}

        bool IsGatePin() override { return true; }
        bool IsInput() { return dir_ == Direction::INPUT; }
        bool IsInout() { return dir_ == Direction::INOUT; }
        bool IsOutput() { return dir_ == Direction::OUTPUT; }

        void SetId(int id) { id_ = id; }
        int GetId() const { return id_; }

        void SetIndex(int index) { index_ = index; }
        int GetIndex() const { return index_; }

        void SetPrimitive(Primitive* primitive) {
            assert(primitive);
            primitive_ = primitive;
        }

        Primitive* GetPrimitive() const { return primitive_; }

    private:
        Direction dir_;
        int index_; // 100.0, 100.1...
        int id_;  // 100
        Primitive* primitive_;

        // todo: add simulation value for learning purpose
    };
}
#endif//NDB_GATE_PIN_H
