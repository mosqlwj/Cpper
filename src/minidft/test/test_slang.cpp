#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "slang/syntax/SyntaxTree.h"
#include "slang/ast/Compilation.h"
#include "slang/ast/ASTVisitor.h"
#include "slang/ast/symbols/CompilationUnitSymbols.h"
#include "slang/ast/symbols/InstanceSymbols.h"
#include "slang/driver/Driver.h"


#include <iostream>
#include <cassert>

using namespace slang;
using namespace slang::ast;
using namespace slang::syntax;


TEST_CASE("SLANG case00") {
    std::cout << "hello slang" << std::endl;
}

TEST_CASE("SLANG case01") {
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


TEST_CASE("SLANG case02") {
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

static std::string getSymbolHierPath(const ast::Symbol& symbol) {

    // Resolve the hierarchical path of the symbol.
    std::string buffer;
    symbol.getHierarchicalPath(buffer);

    return buffer;
}

class VariableReferenceVisitor : public ast::ASTVisitor<VariableReferenceVisitor, false, true> {
public:

    void handle(const slang::ast::NamedValueExpression& expr) {

    }

    void handle(const slang::ast::ElementSelectExpression& expr) {
        selectors_.push_back(&expr);
        expr.value().visit(*this);
    }

    void handle(const slang::ast::RangeSelectExpression& expr) {
        selectors_.push_back(&expr);
        expr.value().visit(*this);
    }

    void handle(const slang::ast::MemberAccessExpression& expr) {
        selectors_.push_back(&expr);
        expr.value().visit(*this);
    }

private:
    std::vector<const ast::Expression*> selectors_;
};

class NetlistVisitor : public slang::ast::ASTVisitor<NetlistVisitor, true, true> {
public:
//    void handle(const slang::ast::InstanceSymbol& symbol) {
//        std::cout << "Instance HierPath: " << getSymbolHierPath(symbol) << std::endl;
//        std::cout << "->Instance: " << symbol.name  << std::endl;
//        std::cout << "->RefModule: " << symbol.getDefinition().name << std::endl;
//        std::cout << "->ParentModule: " << symbol.getParentScope()->asSymbol().name << std::endl;
//        std::cout << "->IsModule: " << symbol.isModule() << std::endl;
//        std::cout << "->IsTop: " << symbol.isTopLevel() << std::endl;
//
//        //
//        for (auto pin_connection : symbol.getPortConnections()) {
//            if (pin_connection->port.kind == slang::ast::SymbolKind::Port) {
//                auto& pin = pin_connection->port.as<slang::ast::PortSymbol>();
//                auto direction = pin.direction;
//                std::cout << "->Pin: " << pin.name << " Direction: " << direction  << std::endl;
//
////                port_connection->getExpression()
//
//            } else {
//                std::cout << "Not support pin kind" << std::endl;
//                assert(false);
//            }
//        }
//
//
//        visitDefault(symbol);
//    }

//    void handle(const slang::ast::UninstantiatedDefSymbol& symbol) {
//        std::cout << "Blackbox Instance HierPath: " << getSymbolHierPath(symbol) << std::endl;
//        std::cout << "->Instance: " << symbol.name << std::endl;
//        std::cout << "->RefModule: " << symbol.definitionName << std::endl;
//
//        auto pin_conns = symbol.getPortConnections();
//        auto pin_names = symbol.getPortNames();
//        for (size_t i = 0; i < pin_conns.size(); i++) {
//            if (!pin_names[i].empty()) {
//                std::cout << "->Pin: " << pin_names[i] << std::endl;
//            }
//
//            std::cout << pin_conns[i]->as<slang::ast::SimpleAssertionExpr>().expr.as<slang::ast::NamedValueExpression>().symbol.name << std::endl;
//
//        }
//
//        visitDefault(symbol);
//    }

    void handle(const slang::ast::InstanceBodySymbol& symbol) {
        std::cout << "Module HierPath: " << getSymbolHierPath(symbol) << std::endl;
        std::cout << "->Module: " << symbol.name << std::endl;
        std::cout << "->Definition: " << symbol.getDefinition().name << std::endl;
        auto ports = symbol.membersOfType<slang::ast::PortSymbol>();
        for (auto& port : ports) {
            std::cout << "->Port: " << port.name << " Direction: " << port.direction << " Width: " << port.getType().toString()<< std::endl;
        }
        auto nets = symbol.membersOfType<slang::ast::NetSymbol>();
        for (auto& net : nets) {
            std::cout << "->Net: " << net.name << " Width: " << net.getType().toString() << std::endl;
        }
//        std::cout << "->port: " <<symbol.memberAt<slang::ast::PortSymbol>(0).name << std::endl;
        visitDefault(symbol);
    }

//    void handle(const slang::ast::PrimitiveInstanceSymbol& symbol) {
//        std::cout << "Primitive: " << symbol.name << " HierPath: " << getSymbolHierPath(symbol) << std::endl;
//        visitDefault(symbol);
//    }

//    void handle(const slang::ast::PortSymbol& symbol) {
//        std::cout << "Port: " << symbol.name << " HierPath: " << getSymbolHierPath(symbol) << std::endl;
//        visitDefault(symbol);
//    }
//
//    void handle(const slang::ast::NetSymbol& symbol) {
//        std::cout << "Net: " << symbol.name << " HierPath: " << getSymbolHierPath(symbol) << std::endl;
//
//        visitDefault(symbol);
//    }


private:

};


TEST_CASE("SLANG case03") {
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

    // Visit the whole tree
    NetlistVisitor visitor;
    compilation.getRoot().visit(visitor);

}