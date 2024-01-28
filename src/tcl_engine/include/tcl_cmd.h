
#ifndef TCL_CMD 
#define TCL_CMD

#include <memory>
#include <iostream>
#include <vector>
#include <map>

#include "tcl_engine.h"

#define REGISTER_TCL_CMD(cmd_class, cmd_name)               \
    dp {                                                    \
        auto cmd_ptr = std::make_unique<cmd_class>(name);   \
        TclCmds::GetTclCmds->AddTclCmd(std::move(cmd_ptr));             \
    } while(0)                                              \

int cmd_proc(ClientData client_data, Tcl_Interp* interp, int objc, struct Tcl_Obj* const* objv);

class TclCmd {

public:
    explicit TclCmd(const char* cmd_name) : cmd_name_{cmd_name} {}

    virtual ~TclCmd();

    const char* GetCmdName() { return cmd_name_; }
    virtual unsigned Check() {
        std::cerr << "This CMD has not defined Check()" << std::endl;
        return 0;
    }

    virtual unsigned Exec() {
        std::cerr << "This CMD has not defined Exec()" << std::endl;
        return 0;
    }
private:

    const char* cmd_name_{nullptr};   
};


class TclCmds {
public:
    TclCmds(const TclCmds&) = delete;
    TclCmds& operator=(const TclCmds&) = delete;
    
    static TclCmds* GetTclCmds() {
        if (tcl_cmds_ == nullptr) {
            tcl_cmds_ = new TclCmds();
        }
        return tcl_cmds_;
    }

    static void DetoryTclCmds() {
        delete tcl_cmds_;
        tcl_cmds_ = nullptr;
    }
    
    void AddTclCmd(std::unique_ptr<TclCmd> cmd) {
        TclEngine::GetTclEngine()->CreateCommand(cmd->GetCmdName(), cmd_proc);
        cmd_map_.emplace(cmd->GetCmdName(), std::move(cmd));
    }
    TclCmd* GetTclCmd(const char* cmd_name) {
        auto it = cmd_map_.find(cmd_name);
        if (it != cmd_map_.end()) {
            return it->second.get();
        }
        return nullptr;
    }

private:
    TclCmds();
    virtual ~TclCmds();
    static TclCmds* tcl_cmds_;
    std::map<const char*, std::unique_ptr<TclCmd>> cmd_map_;

};


int cmd_proc(ClientData client_data, Tcl_Interp* interp, int objc, struct Tcl_Obj* const* objv) {

    // 获取指令名称
    const char* cmd_name = Tcl_GetString(objv[0]);
    TclCmd* cmd = TclCmds::GetTclCmds()->GetTclCmd(cmd_name);

    return cmd->Exec();

}

#endif