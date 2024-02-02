#ifndef READ_VERILOG_CMD_H
#define READ_VERILOG_CMD_H



#include "tcl_cmd.h"

class ReadVerilogCmd : public TclCmd {
public:

    // 构造函数
    // 传入命令名，用于在解释器中调用命令   
    ReadVerilogCmd(const char* cmd_name) : TclCmd(cmd_name) {
        app_->add_option(cmd_name, file_path_, "Read verilog file")->required()->check(CLI::ExistingFile);
    }
    
    // 析构函数
    ~ReadVerilogCmd() {}

    unsigned Check() override {
        return TCL_OK;
    }

    // 执行命令
    unsigned Exec() override {
        std::cout << "Run ReadVerilogCmd" << std::endl;
        std::cout << cmd_name_ << " " << file_path_ << std::endl;
        return TCL_OK;
    }

private:

    std::string file_path_;
//     bool help_flag_ = false;
    
};



#endif /* HELP_CMD_H */