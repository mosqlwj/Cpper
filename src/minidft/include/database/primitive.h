//
// Created by liwenjie on 2024/6/3.
//

/*
 * @description: for flatten model
 */
#ifndef NDB_PRIMITIVE_H
#define NDB_PRIMITIVE_H

#include "object.h"
#include "gate_pin.h"

#include <vector>
#include <string>
#include <unordered_map>


namespace ndb {
    class Net;

    enum class PrimitiveType {
        UNDEFINED,
        PI,
        PO,

        AND,
        NAND,
        OR,
        NOR,
        INV,
        BUF,
        XOR,
        XNOR,
        TSL,
        TSLI,
        TSH,
        TSHI,
        MUX,
        DFF,
        DLAT,
        XDET,
        WIRE,
        PULLUP,
        PULLDOWN,
        TIE0,
        TIE1,
        TIEX,
        TIEZ,

    };

    const std::unordered_map<std::string, PrimitiveType> Name2PrimitiveType = {
            {"PI", PrimitiveType::PI},
            {"PO", PrimitiveType::PO},

            {"AND", PrimitiveType::AND},
            {"NAND", PrimitiveType::NAND},
            {"OR", PrimitiveType::OR},
            {"NOR", PrimitiveType::NOR},
            {"INV", PrimitiveType::INV},
            {"BUF", PrimitiveType::BUF},
            {"XOR", PrimitiveType::XOR},
            {"XNOR", PrimitiveType::XNOR},
            {"TSL", PrimitiveType::TSL},
            {"TSLI", PrimitiveType::TSLI},
            {"TSH", PrimitiveType::TSH},
            {"TSHI", PrimitiveType::TSHI},
            {"MUX", PrimitiveType::MUX},
            {"DFF", PrimitiveType::DFF},
            {"DLAT", PrimitiveType::DLAT},
            {"XDET", PrimitiveType::XDET},
            {"WIRE", PrimitiveType::WIRE},
            {"PULLUP", PrimitiveType::PULLUP},
            {"PULLDOWN", PrimitiveType::PULLDOWN},
            {"TIE0", PrimitiveType::TIE0},
            {"TIE1", PrimitiveType::TIE1},
            {"TIEX", PrimitiveType::TIEX},
            {"TIEZ", PrimitiveType::TIEZ},
    };


    class Primitive : public Object {

    public:
        Primitive(const std::string& name, PrimitiveType type) : Object(name), type_(type) {}
        bool IsPrimitive() override { return true; }

        void SetId(int id) { id_ = id; }
        int GetId() const { return id_; }

        void SetType(PrimitiveType type) { type_ = type; }
        PrimitiveType GetType() const { return type_; }

        void AddInputGatePin(GatePin* pin) { input_gate_pin_.push_back(pin); }
        auto GetInputGatePins() const { return input_gate_pin_; }
        void AddOutputGatePin(GatePin* pin) { output_gate_pin_.push_back(pin); }
        auto GetOutputGatePins() const { return output_gate_pin_; }

        void AddInputNet(Net* net) { input_net_.push_back(net); }
        auto GetInputNets() const { return input_net_; }
        void AddOutputNet(Net* net) { output_net_.push_back(net); }
        auto GetOutputNets() const { return output_net_; }

    private:
        int id_;
        PrimitiveType type_{PrimitiveType::UNDEFINED};

        std::vector<GatePin*> input_gate_pin_;  // multiple input
        std::vector<Net*> input_net_;

        std::vector<GatePin*> output_gate_pin_; // only one output
        std::vector<Net*> output_net_;
    };
}
#endif//NDB_PRIMITIVE_H
