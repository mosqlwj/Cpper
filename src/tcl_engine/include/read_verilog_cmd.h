#ifndef READ_VERILOG_CMD_H
#define READ_VERILOG_CMD_H



#include "tcl_cmd.h"

class ReadVerilogCmd : public TclCmd {
public:

    // 构造函数
    // 传入命令名，用于在解释器中调用命令   
    ReadVerilogCmd(const char* cmd_name) : TclCmd(cmd_name) {
        // app_->add_option("-file", 1, "verilog file path");
    }
    
    // 析构函数
    ~ReadVerilogCmd() {}

    unsigned Check() override {
        return TCL_OK;
    }

    // 执行命令
    unsigned Exec() override {
        std::cout << "Run ReadVerilogCmd" << std::endl;
        return TCL_OK;
    }

// private:
//     bool help_flag_ = false;
    
};



#endif /* HELP_CMD_H */