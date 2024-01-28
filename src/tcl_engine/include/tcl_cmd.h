
#ifndef TCL_CMD 
#define TCL_CMD

#include <memory>

#define REGISTER_TCL_CMD(cmd_class, cmd_name)               \
    dp {                                                    \
        auto cmd_ptr = std::make_unique<cmd_class>(name);   \
        TclCmds::AddTclCmd(std::move(cmd_ptr));             \
    } while(0)                                              \


class TclCmd {
private:
    /* data */
public:
   
};


class TclCmds {
public:

private:

}


#endif