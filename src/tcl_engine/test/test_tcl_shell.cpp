#include "tcl_shell.h"
#include "tcl_cmd.h"
#include "read_verilog_cmd.h"
#include "set_thread_num_cmd.h"

int Tcl_AppInit( Tcl_Interp *interp) {
   if( Tcl_Init( interp ) == TCL_ERROR) {
      return TCL_ERROR;
   }

   REGISTER_TCL_CMD(ReadVerilogCmd, "read_verilog");
   REGISTER_TCL_CMD(SetThreadNumCmd, "set_thread_num");

 
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
int registerCommands() {
    REGISTER_TCL_CMD(ReadVerilogCmd, "read_verilog");
    REGISTER_TCL_CMD(SetThreadNumCmd, "set_thread_num");
    return 0;
}
int main(int argc, char* argv[]) {
    auto* shell = TclShell::GetTclShell();
    shell->SetUserInit(registerCommands);
    CLI::App app("tcl shell");
    bool show_version = false;
    std::string script_file;
    app.add_option("-f,--file", script_file, "tcl script file to execute");
    app.add_flag("-V,--version", show_version, "show version");
    CLI11_PARSE(app, argc, argv);
    shell->DisplayHello();
    if (show_version) {
        std::cout << "tcl shell version 1.0" << std::endl;  
        return 0;
    }

    if   (!script_file.empty()) {
        shell->Run(script_file.c_str());
    } else {

        shell->DisplayHelp();
        shell->Run(argc, argv);
    }
    
    return 0;
}