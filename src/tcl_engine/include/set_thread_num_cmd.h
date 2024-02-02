#ifndef SET_THREAD_NUM_CMD_H
#define SET_THREAD_NUM_CMD_H    



#include "tcl_cmd.h"

class SetThreadNumCmd : public TclCmd {
public:

    // 构造函数
    // 传入命令名，用于在解释器中调用命令   
    SetThreadNumCmd(const char* cmd_name) : TclCmd(cmd_name) {
        app_->add_subcommand(cmd_name, "Set the number of threads to use for parallel processing");
        app_->add_option("-n,--num-threads", thread_num_, "Number of threads")->required()->check(CLI::Range(1, 1000));
    }
    
    // 析构函数
    ~SetThreadNumCmd() {}

    unsigned Check() override {
        return TCL_OK;
    }

    // 执行命令
    unsigned Exec() override {
        std::cout << "Run SetThreadNumCmd" << std::endl;
        std::cout << cmd_name_ << " -n " << thread_num_ << std::endl;
        return TCL_OK;
    }

private:

    int thread_num_ = 1;
//     bool help_flag_ = false;
    
};



#endif /* HELP_CMD_H */