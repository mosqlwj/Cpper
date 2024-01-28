#include <tcl.h>

#ifndef TCL_ENGINE
#define TCL_ENGINE

class TclEngine {
    public:
        TclEngine(const TclEngine&) = delete;
        TclEngine& operator=(const TclEngine&) = delete;

        // todo:线程安全
        static TclEngine* GetTclEngine() {
            if (tcl_engine_ == nullptr) {
                tcl_engine_ = new TclEngine();
            }
            return tcl_engine_;
        }

        static void DestroyTclEngine() {
            delete tcl_engine_;
            tcl_engine_ = nullptr;
        }

        Tcl_Interp* GetTclInterp() {
            return tcl_interp_;
        }

        Tcl_Command CreateCommand(const char* cmd_name, Tcl_ObjCmdProc* cmd_proc) {
            return Tcl_CreateObjCommand(tcl_interp_, cmd_name, cmd_proc, nullptr, nullptr);
        }


        int EvalFile(const char* cmd_file) {
            return Tcl_EvalFile(tcl_interp_, cmd_file);
        }

        int EvalString(const char* cmd_str) {
            return Tcl_Eval(tcl_interp_, cmd_str);
        }

        void SetResult(char* result) {
            Tcl_SetResult(tcl_interp_, result, nullptr);
        }

        void AppendResult(char* result) {
            Tcl_AppendResult(tcl_interp_, result, nullptr);
        }

        const char* GetResult() {
            return Tcl_GetStringResult(tcl_interp_);
        }
    private:
        TclEngine();
        virtual ~TclEngine();

        static TclEngine* tcl_engine_;
        Tcl_Interp* tcl_interp_{nullptr};    
};

#endif