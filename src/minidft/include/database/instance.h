//
// Created by liwenjie on 2024/6/3.
//

#ifndef NDB_INSTANCE_H
#define NDB_INSTANCE_H

#include "object.h"
#include <vector>
#include <unordered_map>

#include "pin.h"



namespace ndb {
    class Module;

    class Instance : public Object {
    public:

        Instance(const std::string& name,
                 const std::string& ref_module_name,
                 const std::string& of_module_name) :
            Object(name),
            ref_module_name_(ref_module_name),
            of_module_name_(of_module_name)
        {
//            parent_ = nullptr;
        }

        bool IsInstance() override { return true; }

//        void SetParent(Instance* parent) { parent_ = parent; }
//        auto GetParent() const { return parent_; }

        void SetRefModuleName(const std::string& ref_module_name) { ref_module_name_ = ref_module_name; }
        auto GetRefModuleName() const { return ref_module_name_; }

        void SetRefModule(Module* ref_module) { ref_module_ = ref_module; }
        auto GetRefModule() const { return ref_module_; }

        void SetOfModuleName(const std::string& of_module_name) { of_module_name_ = of_module_name; }
        auto GetOfModuleName() const { return of_module_name_; }

        void SetBlackbox(bool is_blackbox) { is_blackbox_ = is_blackbox; }
        bool IsBlackbox() { return is_blackbox_; }

        void AddPin(Pin* pin) {
            assert(pin);
            pins_.push_back(pin);
            name_to_pin_[pin->GetName()] = pin;
        }
        auto GetPins() const { return pins_; }
        Pin* GetPinByName(const std::string& name)  {
            if (name_to_pin_.find(name) != name_to_pin_.end()) {
                return name_to_pin_[name];
            }
            return nullptr;
        }

        void AddPinBus(PinBus* pinbus) {
            assert(pinbus);
            pinbuses_.push_back(pinbus);
            name_to_pinbus_[pinbus->GetName()] = pinbus;
        }

        auto GetPinBuses() const { return pinbuses_; }

        PinBus* GetPinBusByName(const std::string& name)  {
            if (name_to_pinbus_.find(name) == name_to_pinbus_.end()) {
                return name_to_pinbus_[name];
            }
            return nullptr;
        }

    private:
        // basic attributes

        //Instance* parent_{nullptr};
        std::string ref_module_name_;
        Module* ref_module_{nullptr};
        std::string of_module_name_;
        Module* of_module_{nullptr};

        bool is_blackbox_;

        std::vector<Pin*> pins_;
        std::vector<PinBus*> pinbuses_;
        std::unordered_map<std::string, Pin*> name_to_pin_;
        std::unordered_map<std::string, PinBus*> name_to_pinbus_;

    private:
        // dft attributes
    };
}
#endif//NDB_INSTANCE_H