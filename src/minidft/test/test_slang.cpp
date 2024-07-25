#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "slang/syntax/SyntaxTree.h"
#include "slang/ast/Compilation.h"
#include "slang/ast/ASTVisitor.h"
#include "slang/ast/symbols/CompilationUnitSymbols.h"
#include "slang/ast/symbols/InstanceSymbols.h"
#include "slang/driver/Driver.h"

#include "database/netlist.h"
#include "verilog_parser/netlist_visitor.h"
using namespace ndb;
using namespace parser;

#include <iostream>
#include <cassert>

using namespace slang;
using namespace slang::ast;
using namespace slang::syntax;


TEST_CASE("SLANG 00") {
    std::cout << "hello slang" << std::endl;
}

TEST_CASE("SLANG 01") {
    std::cout << "hello slang1" << std::endl;
    auto tree = slang::syntax::SyntaxTree::fromText(R"(
module m;
    initial begin
        if (1) begin
            int i = {1 + 2, 5 + 6};
        end
    end
    int j = 3 + 4;
endmodule
)");

    slang::ast::Compilation compilation;
    compilation.addSyntaxTree(tree);

    // Visit the whole tree and count the binary expressions.
    int count = 0;
    compilation.getRoot().visit(slang::ast::makeVisitor([&](auto& v, const BinaryExpression& expr) {
        count++;
        v.visitDefault(expr);
    }));


    std::cout << "hello slang2, count = " << count << std::endl;
}


TEST_CASE("SLANG 02") {
    std::cout << "hello slang1" << std::endl;
    auto tree = slang::syntax::SyntaxTree::fromText(R"(
module INVX1 (A, Y);
input  A ;
output Y ;
   not I0(Y, A);
endmodule

module NAND2X2 (A, B, Y);
input  A, B ;
output Y ;
wire I0_out;
   and I0(I0_out, A, B);
   not I1(Y, I0_out);
endmodule

module s27(G0, G1, G2);
  input G0, G1;
  output G2;
  wire n_1;

  INVX1 g81(.A (G0), .Y (n_1));
  NAND2X2 g17(.A (G1), .B (n_1), .Y (G2));
endmodule
)");

    slang::ast::Compilation compilation;
    compilation.addSyntaxTree(tree);

    // Visit the whole tree and count the binary expressions.

    compilation.getRoot().visit(slang::ast::makeVisitor([&](auto& v, const InstanceSymbol& type) {
        std::cout << type.name << std::endl;
        std::cout << type.getDefinition().name << std::endl;
        v.visitDefault(type);
    }));


    std::cout << "hello slang2" << std::endl;
}




TEST_CASE("SLANG case03") {
    auto tree = slang::syntax::SyntaxTree::fromText(R"(
// 测试concat

module M1(A, B);
    input [3:0] A;
    output B;
endmodule

module case03(G0, G1, G2, G3);
  input G0;
  input [1:0] G1;
  input [3:0] G2;
  output G3;
  wire n_1;
  M1 inst1(.A({G0, G1[0], G2[3:2]}), .B(n_1));
endmodule
)");
    CompilationOptions options;
    options.flags |= slang::ast::CompilationFlags::IgnoreUnknownModules;
    options.flags |= slang::ast::CompilationFlags::AllowUseBeforeDeclare;
    Bag bag;
    bag.set(options);
    slang::ast::Compilation compilation(bag);
    std::cout << "Flag IgnoreUnknownModules: " << compilation.hasFlag(slang::ast::CompilationFlags::IgnoreUnknownModules) << std::endl;
    std::cout << "Flag AllowUseBeforeDeclare: " << compilation.hasFlag(slang::ast::CompilationFlags::AllowUseBeforeDeclare) << std::endl;
    compilation.addSyntaxTree(tree);

    // creat netlist and library
    Library* lib = new Library("sky130");
    //    lib->ReadLibrary();
    Netlist* netlist = new Netlist();
    netlist->SetLibrary(lib);

    // Visit the whole tree
    NetlistVisitor visitor;
    compilation.getRoot().visit(visitor);

}

TEST_CASE("SLANG case04") {
    auto tree = slang::syntax::SyntaxTree::fromText(R"(
module INVX1 (A, Y);
input  A ;
output Y ;

endmodule

module case011(G0, G1, G2);
  input G0, G1;
  output G2;
  wire n_1;

  INVX1 g81(.A (G0), .Y (n_1));
  NAND2X2 g17(.A (G1), .B (n_1), .Y (G2));
endmodule
)");
    CompilationOptions options;
    options.flags |= slang::ast::CompilationFlags::IgnoreUnknownModules;
    options.flags |= slang::ast::CompilationFlags::AllowUseBeforeDeclare;
    Bag bag;
    bag.set(options);
    slang::ast::Compilation compilation(bag);
    std::cout << "Flag IgnoreUnknownModules: " << compilation.hasFlag(slang::ast::CompilationFlags::IgnoreUnknownModules) << std::endl;
    std::cout << "Flag AllowUseBeforeDeclare: " << compilation.hasFlag(slang::ast::CompilationFlags::AllowUseBeforeDeclare) << std::endl;
    compilation.addSyntaxTree(tree);

    // creat netlist and library
    Library* lib = new Library("sky130");
//    lib->ReadLibrary();
    Netlist* netlist = new Netlist();
    netlist->SetLibrary(lib);

    // Visit the whole tree
    NetlistVisitor visitor;
    compilation.getRoot().visit(visitor);

}

TEST_CASE("SLANG case05") {
    auto tree = slang::syntax::SyntaxTree::fromText(R"(
module NAND2X2 (A, B, Y);
input  A, B;
output Y ;

endmodule

module case01(G0, G1);
  input[1:0] G0;
  output G1;

  NAND2X2 g17(.A (G0[0]), .B (G0[1]), .Y (G1));
endmodule
)");
    CompilationOptions options;
    options.flags |= slang::ast::CompilationFlags::IgnoreUnknownModules;
    options.flags |= slang::ast::CompilationFlags::AllowUseBeforeDeclare;
    Bag bag;
    bag.set(options);
    slang::ast::Compilation compilation(bag);
    std::cout << "Flag IgnoreUnknownModules: " << compilation.hasFlag(slang::ast::CompilationFlags::IgnoreUnknownModules) << std::endl;
    std::cout << "Flag AllowUseBeforeDeclare: " << compilation.hasFlag(slang::ast::CompilationFlags::AllowUseBeforeDeclare) << std::endl;
    compilation.addSyntaxTree(tree);

    // creat netlist and library
    Library* lib = new Library("sky130");
    //    lib->ReadLibrary();
    Netlist* netlist = new Netlist();
    netlist->SetLibrary(lib);

    // Visit the whole tree
    NetlistVisitor visitor;
    compilation.getRoot().visit(visitor);

}

TEST_CASE("SLANG case06") {
    auto tree = slang::syntax::SyntaxTree::fromText(R"(
// 测试Const
module NAND2X2 (A, B, Y);
input  A, B;
output Y ;

endmodule

module case01(G1);
  output G1;

  NAND2X2 g17(.A (1'b0), .B (1'b1), .Y (G1));
endmodule
)");
    CompilationOptions options;
    options.flags |= slang::ast::CompilationFlags::IgnoreUnknownModules;
    options.flags |= slang::ast::CompilationFlags::AllowUseBeforeDeclare;
    Bag bag;
    bag.set(options);
    slang::ast::Compilation compilation(bag);
    std::cout << "Flag IgnoreUnknownModules: " << compilation.hasFlag(slang::ast::CompilationFlags::IgnoreUnknownModules) << std::endl;
    std::cout << "Flag AllowUseBeforeDeclare: " << compilation.hasFlag(slang::ast::CompilationFlags::AllowUseBeforeDeclare) << std::endl;
    compilation.addSyntaxTree(tree);

    // creat netlist and library
    Library* lib = new Library("sky130");
    //    lib->ReadLibrary();
    Netlist* netlist = new Netlist();
    netlist->SetLibrary(lib);

    // Visit the whole tree
    NetlistVisitor visitor;
    compilation.getRoot().visit(visitor);

}