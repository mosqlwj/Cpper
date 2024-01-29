#include "tcl_cmd.h"

TclCmds::TclCmds() {

}

TclCmds::~TclCmds() {

}
    

TclCmds* TclCmds::tcl_cmds_ = nullptr;

void GetArgvFromTclObj(int objc, Tcl_Obj* const* objv, char* argv[]) {
        for (int i = 0; i < objc; i++) {
            argv[i] = Tcl_GetString(objv[i]);
        }
    }

int CmdProc(ClientData client_data, Tcl_Interp* interp, int objc, Tcl_Obj* const* objv) {

    // 获取指令参数
    std::vector<char*> argv(objc);
    GetArgvFromTclObj(objc, objv, argv.data());

    // 获取指令名称
    const char* cmd_name = Tcl_GetString(objv[0]);
    TclCmd* cmd = TclCmds::GetTclCmds()->GetTclCmd(cmd_name);

    if (cmd == nullptr) {
        std::cerr << "Can not find cmd: " << cmd_name << std::endl;
        return TCL_ERROR;
    }

    // 解析指令参数
    if (!cmd->Parse(objc, argv.data())) {
        return TCL_ERROR;
    }

    // 检查指令参数
    if (cmd->Check() != 0) {
        return TCL_ERROR;
    }

    // 执行指令
    if (cmd->Exec() != 0) {
        return TCL_ERROR;
    }

    return TCL_OK;

}
