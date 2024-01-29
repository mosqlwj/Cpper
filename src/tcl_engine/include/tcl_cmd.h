
#ifndef TCL_CMD_H
#define TCL_CMD_H



#include <memory>
#include <iostream>
#include <vector>
#include <map>

#include "tcl_engine.h"
#include "CLI11.hpp"





/*
 * 指令处理函数
 * @param client_data 客户端数据
 * @param interp Tcl解释器
 * @param objc 指令参数个数
 * @param objv 指令参数
 * @return 0表示成功，非0表示失败
 */
extern int CmdProc(ClientData client_data, Tcl_Interp* interp, int objc, Tcl_Obj* const* objv);

/*
 * 从Tcl_Obj数组中获取指令参数
 * @param objc 指令参数个数
 * @param objv 指令参数
 * @param argv 指令参数数组
 */
extern void GetArgvFromTclObj(int objc, Tcl_Obj* const* objv, char* argv[]);


class TclCmd {

public:
    explicit TclCmd(const char* cmd_name) : cmd_name_{cmd_name} {
        app_ = new CLI::App(cmd_name_);
    }

    virtual ~TclCmd() {
        delete app_;
        app_ = nullptr;
    }

    const char* GetCmdName() { return cmd_name_; }

    virtual bool Parse(int argc, char* argv[]) {
        CLI11_PARSE(*app_, argc, argv);
        return true;
    }

    virtual unsigned Check() {
        std::cerr << "This CMD has not implemented Check()" << std::endl;
        return 0;
    }

    virtual unsigned Exec() {
        std::cerr << "This CMD has not implemented Exec()" << std::endl;
        return 0;
    }

protected:
    CLI::App* app_{nullptr}; // CLI11应用对象
    
private:

    const char* cmd_name_{nullptr}; // 指令名称
    
     
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
        TclEngine::GetTclEngine()->CreateCommand(cmd->GetCmdName(), CmdProc);
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


/*
 * 注册指令
 * @param cmd_class 指令类
 * @param cmd_name 指令名称
 */
// extern void RegisterTclCmd(TclCmd* cmd_class, const char* cmd_name) {
//     auto cmd_ptr = std::make_unique<TclCmd>(cmd_name);
//     TclCmds::GetTclCmds()->AddTclCmd(std::move(cmd_ptr));
// }
#define REGISTER_TCL_CMD(cmd_class, cmd_name)               \
    do {                                                    \
        auto cmd_ptr = std::make_unique<cmd_class>(cmd_name);   \
        TclCmds::GetTclCmds()->AddTclCmd(std::move(cmd_ptr));             \
    } while(0)                                              




#endif