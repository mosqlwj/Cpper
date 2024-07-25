//
// Created by liwenjie on 2024/7/25.
//

#ifndef PARSER_NETLIST_VISITOR_H
#define PARSER_NETLIST_VISITOR_H

#include "database/object.h"
#include "database/netlist.h"

#include "slang/syntax/SyntaxTree.h"
#include "slang/ast/Compilation.h"
#include "slang/ast/ASTVisitor.h"
#include "slang/ast/symbols/CompilationUnitSymbols.h"
#include "slang/ast/symbols/InstanceSymbols.h"
#include "slang/driver/Driver.h"

using namespace ndb;

namespace parser {

    static std::string getSymbolHierPath(const slang::ast::Symbol& symbol) {

        // Resolve the hierarchical path of the symbol.
        std::string buffer;
        symbol.getHierarchicalPath(buffer);

        return buffer;
    }

    class NetlistVisitor : public slang::ast::ASTVisitor<NetlistVisitor, true, true> {
    public:

        void handle(const slang::ast::InstanceBodySymbol& symbol) {
            std::cout << "Module HierPath: " << getSymbolHierPath(symbol) << std::endl;
            std::cout << "->Module: " << symbol.name << std::endl;
            std::cout << "->Definition: " << symbol.getDefinition().name << std::endl;

            // ports
            auto ports = symbol.membersOfType<slang::ast::PortSymbol>();
            for (auto& port : ports) {
                std::cout << "->Port: " << port.name << ", Direction: " << port.direction << ", Width: " << port.getType().toString()<< std::endl;
            }

            // nets
            auto nets = symbol.membersOfType<slang::ast::NetSymbol>();
            for (auto& net : nets) {
                std::cout << "->Net: " << net.name << ", Width: " << net.getType().toString() << std::endl;
            }

            // Assign

            // InstanceSymbol
            auto instances = symbol.membersOfType<slang::ast::InstanceSymbol>();
            for (auto& instance : instances) {
                std::cout << "Instance HierPath: " << getSymbolHierPath(instance) << std::endl;
                std::cout << "->Instance: " << instance.name  << std::endl;
                std::cout << "->RefModule: " << instance.getDefinition().name << std::endl;
                std::cout << "->ParentModule: " << instance.getParentScope()->asSymbol().name << std::endl;
                std::cout << "->IsModule: " << instance.isModule() << std::endl;
                std::cout << "->IsTop: " << instance.isTopLevel() << std::endl;

                //
                for (auto pin_connection : instance.getPortConnections()) {
                    if (pin_connection->port.kind == slang::ast::SymbolKind::Port) {
                        auto& pin = pin_connection->port.as<slang::ast::PortSymbol>();
                        auto direction = pin.direction;
                        auto net = HandleExpression(pin_connection->getExpression());
                        std::cout << "->Pin: " << pin.name << ", Direction: " << direction << ", Net:" << net  << std::endl;

                    } else {
                        std::cout << "Not support pin kind" << std::endl;
                        assert(false);
                    }
                }
            }

            // UninstancedDefSymbol
            auto uninstantiated_defs = symbol.membersOfType<slang::ast::UninstantiatedDefSymbol>();
            for (auto& uninstantiated_def : uninstantiated_defs) {
                std::cout << "Blackbox Instance HierPath: " << getSymbolHierPath(uninstantiated_def) << std::endl;
                std::cout << "->Instance: " << uninstantiated_def.name << std::endl;
                std::cout << "->RefModule: " << uninstantiated_def.definitionName << std::endl;

                auto pin_conns = uninstantiated_def.getPortConnections();
                auto pin_names = uninstantiated_def.getPortNames();
                for (size_t i = 0; i < pin_conns.size(); i++) {
                    if (!pin_names[i].empty()) {
                        auto net = HandleExpression(&pin_conns[i]->as<slang::ast::SimpleAssertionExpr>().expr);
                        std::cout << "->Pin: " << pin_names[i]  << ", Net:" << net << std::endl;
                    }
                }
            }

            //
            visitDefault(symbol);
        }

    private:
        void HandleInstanceSymbol();
        void HandleUninstantiatedDefSymbol();

        std::string HandleExpression(const slang::ast::Expression* expr) {
            switch (expr->kind) {
                case slang::ast::ExpressionKind::NamedValue: {
                    return HandleNamedValueExpression(expr->as<slang::ast::NamedValueExpression>());
                }
                case slang::ast::ExpressionKind::Assignment: {
                    return HandleAssignmentExpression(expr->as<slang::ast::AssignmentExpression>());
                }
                case slang::ast::ExpressionKind::ElementSelect: {
                    return HandleElementSelectExpression(expr->as<slang::ast::ElementSelectExpression>());
                }
                case slang::ast::ExpressionKind::RangeSelect: {
                    return HandleRangeSelectExpression(expr->as<slang::ast::RangeSelectExpression>());
                }
                case slang::ast::ExpressionKind::Concatenation: {
                    return HandleConcatExpression(expr->as<slang::ast::ConcatenationExpression>());
                }
                case slang::ast::ExpressionKind::Conversion: {
                    return HandleConversionExpression(expr->as<slang::ast::ConversionExpression>());
                }
                default:
                    assert(false);
                    break;
            }
        }

        std::string HandleNamedValueExpression(const slang::ast::NamedValueExpression& expr) {
            return std::string(expr.symbol.name);
        }

        std::string HandleElementSelectExpression(const slang::ast::ElementSelectExpression& expr) {
            return std::string(expr.value().getSymbolReference()->name) + "[" + expr.selector().constant->toString() + "]";
        }

        std::string HandleRangeSelectExpression(const slang::ast::RangeSelectExpression& expr) {
            return std::string(expr.value().getSymbolReference()->name) +
                   "[" + expr.left().constant->toString() +
                   ":" + expr.right().constant->toString() +
                   "]";

        }

        std::string HandleConversionExpression(const slang::ast::ConversionExpression& expr) {
            return expr.constant->toString();
        }

        std::string HandleConcatExpression(const slang::ast::ConcatenationExpression& expr) {
            std::string result;
            result += "{";
            for (auto& elem : expr.operands()) {
                if (elem->kind == slang::ast::ExpressionKind::NamedValue) {
                    result += HandleNamedValueExpression(elem->as<slang::ast::NamedValueExpression>()) + " ";
                } else if (elem->kind == slang::ast::ExpressionKind::ElementSelect) {
                    result += HandleElementSelectExpression(elem->as<slang::ast::ElementSelectExpression>()) + " ";
                } else if (elem->kind == slang::ast::ExpressionKind::RangeSelect) {
                    result += HandleRangeSelectExpression(elem->as<slang::ast::RangeSelectExpression>()) + " ";
                } else if (elem->kind == slang::ast::ExpressionKind::Conversion) {
                    result += HandleConversionExpression(elem->as<slang::ast::ConversionExpression>()) + " ";
                } else if (elem->kind == slang::ast::ExpressionKind::Concatenation) {
                    result += HandleConcatExpression(elem->as<slang::ast::ConcatenationExpression>()) + " ";
                } else {
                    assert(false);
                }

            }
            result += "}";
            return result;
        }

        std::string HandleAssignmentExpression(const slang::ast::AssignmentExpression& expr) {
            auto& left = expr.left();
            if (left.kind == slang::ast::ExpressionKind::NamedValue) {
                return HandleNamedValueExpression(left.as<slang::ast::NamedValueExpression>()) + " ";
            } else if (left.kind == slang::ast::ExpressionKind::ElementSelect) {
                return HandleElementSelectExpression(left.as<slang::ast::ElementSelectExpression>()) + " ";
            } else if (left.kind == slang::ast::ExpressionKind::RangeSelect) {
                return HandleRangeSelectExpression(left.as<slang::ast::RangeSelectExpression>()) + " ";
            } else if (left.kind == slang::ast::ExpressionKind::Conversion) {
                return HandleConversionExpression(left.as<slang::ast::ConversionExpression>()) + " ";
            } else if (left.kind == slang::ast::ExpressionKind::Concatenation) {
                return HandleConcatExpression(left.as<slang::ast::ConcatenationExpression>()) + " ";
            } else {
                assert(false);
            }
        }

    private:
        Netlist* netlist_{nullptr};
    };
}
#endif//PARSER_NETLIST_VISITOR_H
