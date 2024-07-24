#ifndef NDB_PORT_H
#define NDB_PORT_H

#include "object.h"
#include "define.h"
#include "bus.h"

#include <string>
#include <cassert>



namespace ndb {
    class Net;
    class PortBus;
    class Module;

    class Port : public Object{
    public:
        Port(const std::string& name, Direction dir) : Object(name), dir_(dir) {}

        bool IsPort() override { return true; }

        bool IsInput() { return dir_ == Direction::INPUT; }
        bool IsInout() { return dir_ == Direction::INOUT; }
        bool IsOutput() { return dir_ == Direction::OUTPUT; }

        void AddConnection(Net* net) {
            assert(net);
            conn_net_ = net;
        }
        Net* GetConnection() const { return conn_net_; }

        void SetIndex(int index) { index_ = index; }
        int GetIndex() const { return index_; }

        void SetOfPortBus(PortBus* bus) {
            assert(bus);
            of_port_bus_ = bus;
        }
        PortBus* GetOfPortBus() const { return of_port_bus_; }

        void SetOfModule(Module* module) {
            assert(module);
            of_module_ = module;
        }

        Module* GetOfModule() const {
            return of_module_;
        }
    private:
        // basic attributes
        Direction dir_{Direction::UNKNOWN};
        Net* conn_net_{nullptr};
        int index_{-1}; // index of port in bus
        PortBus* of_port_bus_{nullptr}; // port bus
        Module* of_module_{nullptr};

        // dft attributes
    };

    class PortBus : public Bus {
    public:
        PortBus(const std::string& name, int left, int right, Direction dir)
            : Bus(name, left, right), dir_(dir) {}

        bool IsPortBus() override { return true; }

        bool IsInput() { return dir_ == Direction::INPUT; }
        bool IsInout() { return dir_ == Direction::INOUT; }
        bool IsOutput() { return dir_ == Direction::OUTPUT; }

        void AddPort(int index, Port* port) {
            assert(InRange(index));
            ports_[index] = port;
        }
        Port* GetPortByIndex(int index) {
            assert(InRange(index));
            return ports_[index];
        }

        void SetOfModule(Module* module) {
            assert(module);
            of_module_ = module;
        }

        Module* GetOfModule() const { return of_module_; }

    private:

        Direction dir_;
        Module* of_module_{nullptr};
        std::unordered_map<int, Port*> ports_;
    };
}

#endif