//
// Created by liwenjie on 2024/6/3.
//

#ifndef NDB_MODULE_H
#define NDB_MODULE_H

#include <vector>
#include <unordered_map>
#include <cassert>

#include "object.h"
#include "port.h"
#include "net.h"
#include "instance.h"
#include "assign.h"



namespace ndb {
    class Module : public Object {
    public:
        Module(const std::string& name) : Object(name)  {}

        bool IsModule() override { return true; }

        void SetBlackbox(bool is_blackbox) { is_blackbox_ = is_blackbox; }
        bool IsBlackbox() { return is_blackbox_; }

        void SetTopModule(bool is_top_module) { is_top_module_ = is_top_module; }
        bool IsTopModule() { return is_top_module_; }

        void AddPort(Port* port) {
            assert(port);
            ports_.emplace_back(port);
            name_to_port_[port->GetName()] = port;
        }
        auto GetPorts() const { return ports_; }
        Port* GetPortByName(const std::string& name) {
            if (name_to_port_.find(name) != name_to_port_.end()) {
                return name_to_port_[name];
            }
            return nullptr;
        }

        void AddPortBus(PortBus* portbus) {
            assert(portbus);
            portbuses_.emplace_back(portbus);
            name_to_portbus_[portbus->GetName()] = portbus;
        }

        PortBus* GetPortBusByName(const std::string& name) {
            if (name_to_portbus_.find(name) != name_to_portbus_.end()) {
                return name_to_portbus_[name];
            }
            return nullptr;
        }
        auto GetPortBuses() const { return portbuses_; }

        void AddNet(Net* net) {
            assert(net);
            nets_.emplace_back(net);
            name_to_net_[net->GetName()] = net;
        }
        Net* GetNetByName(const std::string& name) {
            if (name_to_net_.find(name) != name_to_net_.end()) {
                return name_to_net_[name];
            }
            return nullptr;
        }
        auto GetNets() const { return nets_; }

        void AddNetBus(NetBus* netbus) {
            assert(netbus);
            netbuses_.emplace_back(netbus);
            name_to_netbus_[netbus->GetName()] = netbus;
        }
        NetBus* GetNetBusByName(const std::string& name) {
            if (name_to_netbus_.find(name) != name_to_netbus_.end()) {
                return name_to_netbus_[name];
            }
            return nullptr;
        }
        auto GetNetBuses() const { return netbuses_; }

        void AddInstance(Instance* instance) {
            assert(instance);
            instances_.emplace_back(instance);
            name_to_instance_[instance->GetName()] = instance;
        }
        Instance* GetInstanceByName(const std::string& name) {
            if (name_to_instance_.find(name) != name_to_instance_.end()) {
                return name_to_instance_[name];
            }
            return nullptr;
        }
        auto GetInstances() const { return instances_; }

        // todo
        // all instances reference of this module

    private:
        // basic attribute

        // include port
        std::vector<Port*> ports_;
        std::unordered_map<std::string, Port*> name_to_port_;

        std::vector<PortBus*> portbuses_;
        std::unordered_map<std::string, PortBus*> name_to_portbus_;

        // include nets
        std::vector<Net*> nets_;
        std::unordered_map<std::string, Net*> name_to_net_;

        std::vector<NetBus*> netbuses_;
        std::unordered_map<std::string, NetBus*> name_to_netbus_;

        // include assign
        std::vector<Assign*> assigns_;

        // include instance
        std::vector<Instance*> instances_; //children
        std::unordered_map<std::string, Instance*> name_to_instance_;

        // black box setting
        bool is_blackbox_ = false;

        bool is_top_module_ = false;

    private:
        // dft attribute
    };
}
#endif//NDB_MODULE_H