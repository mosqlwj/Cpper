#include "tcl_engine.h"

TclEngine::TclEngine() {
    tcl_interp_ = Tcl_CreateInterp();
}

TclEngine::~TclEngine() {
    Tcl_DeleteInterp(tcl_interp_);
}

TclEngine* TclEngine::tcl_engine_ = nullptr;