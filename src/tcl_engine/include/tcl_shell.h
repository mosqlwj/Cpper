#ifndef TCL_SHELL_H
#define TCL_SHELL_H

#include "tcl_engine.h"
#include <iostream>

class TclShell {
public:
    TclShell(const TclShell&) = delete;
    TclShell& operator=(const TclShell&) = delete;

    static TclShell* GetTclShell() {
        if (tcl_shell_ == nullptr) {            
            tcl_shell_ = new TclShell();       
        }
        return tcl_shell_;
    }

    static void SetUserInit(int (*init)()) {
        user_init_ = init;
    }

    static int Run(const char* script) {
        int argc = 2;
        char* argv[2] = { const_cast<char*>("TclShell"), nullptr };
        argv[1] = const_cast<char*>(script);
        // delete[] argv;
        return Run(argc, argv);
        
    }

    static int Run(int argc, char* argv[]) {
        auto* tcl_engine = TclEngine::GetTclEngine();
        Tcl_Interp* interp = tcl_engine->GetTclInterp();
        Tcl_MainEx(argc, argv, TclAppInit, interp);
        return 0;
    }


    static void DisplayHello() {
        std::cout << "Hello, TclShell!" << std::endl;
    }
    static void DisplayHelp() {
        std::cout << "Usage: tclsh [script]" << std::endl;
    }




private:
    static int TclAppInit(Tcl_Interp *interp) {
        return user_init_();
    }
    static int (*user_init_)();

    TclShell() {

    }
    virtual ~TclShell() {
        
    }
    static TclShell* tcl_shell_;
};

TclShell* TclShell::tcl_shell_ = nullptr;

static int DefaultUserInit() {
    std::cout << "TclShell default user init" << std::endl;
    return 0;
}

int (*TclShell::user_init_)() = DefaultUserInit;

#endif /* TCL_SHELL_H */