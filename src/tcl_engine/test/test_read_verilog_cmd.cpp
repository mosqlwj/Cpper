
#include <iostream>
#include <vector>
#include <string>

#include "tcl_engine.h"
#include "tcl_cmd.h"
#include "read_verilog_cmd.h"

int Tcl_AppInit( Tcl_Interp *interp) {
   if( Tcl_Init( interp ) == TCL_ERROR) {
      return TCL_ERROR;
   }

   REGISTER_TCL_CMD(ReadVerilogCmd, "read_verilog");

 
   std::string commands("");
   commands += "proc prompt1 {} {\n";
   commands += "  puts -nonewline \"CASDFT> \"\n";
   commands += "  flush stdout\n";
   commands += "}\n";
   commands += "proc prompt2 {} {\n";
   commands += "  puts -nonewline \"> \"\n";
   commands += "  flush stdout\n";
   commands += "}\n";
   commands += "set ::tcl_prompt1 prompt1\n";
   commands += "set ::tcl_prompt2 prompt2\n";

   Tcl_Eval( interp, commands.c_str());

  
   return TCL_OK;
}

int main(int argc, char* argv[]) {
   
    Tcl_MainEx(argc, argv, Tcl_AppInit, TclEngine::GetTclEngine()->GetTclInterp());

    return 0;
}