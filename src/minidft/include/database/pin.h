#ifndef NDB_PIN_H
#define NDB_PIN_H

#include "object.h"
#include "define.h"
#include "bus.h"

#include <string>
#include <cassert>



namespace ndb {
    class PinBus;
    class Instance;
    class Net;

    class Pin : public Object{

    public:
        Pin(const std::string& name, Direction dir) : Object(name), dir_(dir) {}

        bool IsPin() override { return true; }

        bool IsInput() { return dir_ == Direction::INPUT; }
        bool IsInout() { return dir_ == Direction::INOUT; }
        bool IsOutput() { return dir_ == Direction::OUTPUT; }

        void SetHierarchyPath(const std::string& hier_path) { hier_path_ = hier_path; }
        std::string GetHierarchyPath() const { return hier_path_; }

        void AddConnection(Object* net) {
            assert(net && net->IsNet());
            conn_ = net;
        }

        Object* GetConnection() const { return conn_; }

        void SetIndex(int index) { index_ = index; }
        int GetIndex() const { return index_; }

        void SetOfPinBus(PinBus* bus) {
            assert(bus);
            of_pin_bus_ = bus;
        }

        PinBus* GetOfPinBus() const { return of_pin_bus_; }

        void SetOfInstance(Instance* instance) {
            assert(instance);
            of_instance_ = instance;
        }

        auto GetOfInstance() const { return of_instance_; }

    private:
        // basic attributes
        Direction dir_{Direction::UNKNOWN};
        std::string hier_path_;
        Object* conn_{nullptr};     // must be single net: {pin, net}
        int index_{-1};             // index of port in bus
        PinBus* of_pin_bus_{nullptr}; // pin bus
        Instance* of_instance_{nullptr};

        //
    };


    class PinBus : public Bus {
    public:
        PinBus(const std::string& name, int left, int right, Direction dir)
            : Bus(name, left, right), dir_(dir) {}

        bool IsPinBus() override { return true; }

        void SetHierarchyPath(const std::string& hier_path) { hier_path_ = hier_path; }
        std::string GetHierarchyPath() const { return hier_path_; }

        bool IsInput() { return dir_ == Direction::INPUT; }
        bool IsInout() { return dir_ == Direction::INOUT; }
        bool IsOutput() { return dir_ == Direction::OUTPUT; }

        void AddPin(int index, Pin* pin) {
            assert(InRange(index));
            pins_[index] = pin;
        }
        Pin* GetPinByIndex(int index) {
            assert(InRange(index));
            return pins_[index];
        }

        void SetOfInstance(Instance* instance) {
            assert(instance);
            of_instance_ = instance;
        }

        auto GetOfInstance() const { return of_instance_; }

        void AddConnection(Object* net) {
            assert(net);
            conn_.push_back(net);
        }

        auto GetConnection() const { return conn_; }

    private:

        Direction dir_{Direction::UNKNOWN};
        std::string hier_path_;
        Instance* of_instance_{nullptr};
        std::unordered_map<int, Pin*> pins_;
        std::vector<Object*> conn_; // connection, include net, netbus, concat,...
    };
}

#endif