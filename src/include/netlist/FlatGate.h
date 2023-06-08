#include <limits>
#include <string>
#include <string_view>
#include <list>
#include <vector>
#include <unordered_map>

namespace netlist {

    using idx_t = std::size_t;
    constexpr idx_t k_invalid_idx = std::numeric_limits<std::size_t>::max();

    enum class GateType {
        T_PI,
        T_PO,
        T_AND,

        T_NONE,
    };

    enum class ObjType {
        GATE_PIN,
        GATE_NET,
        GATE_,
        GATE_NETLIST,
        NONE,
    };

    enum class GatePinDir {
        INPUT,
        OUTPUT,
        INOUT,
        NONE,
    };

    struct Object {
        Object(idx_t obj_id, ObjType obj_type) 
            : obj_id_(obj_id), obj_type_(obj_type) {}

        idx_t   obj_id_{k_invalid_idx};
        ObjType obj_type_{ObjType::NONE}; 
    };


    struct GatePin : public Object {
        
        GatePin(idx_t obj_id, ObjType obj_type, GatePinDir dir, const std::string& name) 
            : Object(obj_id, obj_type), direction_(dir), name_(name) {}

        GatePinDir direction_{GatePinDir::NONE};
        idx_t ref_gate_id_{k_invalid_idx}; // for connecting gate
        idx_t index_{k_invalid_idx};   // 0:out, 1:in1, 2:in2 ...
        idx_t ref_net_id_{k_invalid_idx};  // for connecting net
        std::string name_;
    };

    struct GateNet : public Object {
        GateNet(idx_t obj_id, ObjType obj_type, const std::string& name) 
            : Object(obj_id, obj_type), name_(name) {} 

        std::string name_;
        std::vector<idx_t> pred_gate_pin_;
        std::vector<idx_t> succ_gate_pin_;
    };

    // flattern gate
    struct FlatGate : public Object{
        FlatGate(idx_t obj_id, ObjType obj_type, GateType gtype, const std::string& name) 
            : Object(obj_id, obj_type), 
              gate_type_(gtype), name_(name) {}

        idx_t level_{k_invalid_idx};
        GateType gate_type_{GateType::T_NONE};
        
        // sim_value for analysis
        // SimValue sim_value_;

        std::vector<idx_t> gate_pin_; // 0:out, 1:in1, 2:in2 ...
        std::vector<idx_t> pred_gate_;
        std::vector<idx_t> succ_gate_;
        
        std::string name_;
    };


    /// @brief flat gate netlist 
    class GateNetlist {
    public:
        
    public:
        std::vector<GatePin> gate_pins_; // vector idx == gate_pin_id_
        std::vector<GateNet> gate_nets_; // vector idx == gate_net_id_
        std::vector<FlatGate> gate_netlist_; // vector idx == gate_id_
        std::unordered_map<std::string, idx_t> name2gate_pin_;
        std::unordered_map<std::string, idx_t> name2gate_net_;
        std::unordered_map<std::string, idx_t> name2gate_;
    };

}