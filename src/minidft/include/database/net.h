#ifndef NDB_NET_H
#define NDB_NET_H

#include "object.h"
#include <string>
#include <vector>
#include <cassert>


namespace ndb {
    class Module;
    class NetBus;

    class Net : public Object{
    public:
        Net(const std::string& name) : Object(name) {}

        bool IsNet() override {
            return true;
        }

        bool IsConst0() {
            return GetName() == "1'b0";
        }

        bool IsContst1() {
            return GetName() == "1'b1";
        }

        bool IsConstX() {
            return GetName() == "1'bx" || GetName() == "1'bX";
        }

        bool IsConstZ() {
            return GetName() == "1'bz" || GetName() == "1'bZ";
        }

        bool IsConst() {
            return IsConst0() || IsContst1() || IsConstX() || IsConstZ();
        }

        void SetIndex(int index) {
            index_ = index;
        }
        int GetIndex() const {
            return index_;
        }
        void SetOfNetBus(NetBus* netbus) {
            assert(of_netbus_ );
            of_netbus_ = netbus;
        }
        NetBus* GetOfNetBus() const {
            return of_netbus_;
        }

        void SetOfModule(Module* module) {
            of_module_ = module;
        }

        Module* GetOfModule() const {
            return of_module_;
        }

        void AddConnection(Object* object) {
            conn_pin_ports_.push_back(object);
        }

        auto GetConnections() const {
            return conn_pin_ports_;
        }

    private:
        // basic attributes
        int index_{-1};
        NetBus* of_netbus_{nullptr};
        Module* of_module_{nullptr};
        std::vector<Object*> conn_pin_ports_; // include port or pin

        // todo: parent instance
    };

    class NetBus : public Bus {
    public:
        NetBus(const std::string& name, int left, int right) : Bus(name, left, right) {}
        bool IsNetBus() override { return true; }


        void AddNet(int index, Net* net) {
            assert(InRange(index));
            nets_[index] = net;
        }

        Net* GetNetByIndex(int index) {
            assert(InRange(index));
            return nets_[index];
        }

        void SetOfModule(Module* module) {
            assert(module);
            of_module_ = module;
        }

        Module* GetOfModule() const { return of_module_; }
    private:
        Module* of_module_{nullptr};
        std::unordered_map<int, Net*> nets_;
    };

    class Concat : public Object {
    public:
        Concat(std::string name) : Object(name) {}

        bool IsConcat() override { return true; }

        void AddObject(Object* object) {
            assert(object);
            concat_.push_back(object);
        }

        auto GetConcat() const { return concat_; }
    private:
        std::vector<Object*> concat_;
    };

    class PartialNet : public NetBus {
    public:

    private:

    };
}

#endif