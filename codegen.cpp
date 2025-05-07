#include "codegen.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

// Helper functions
static void generateStatement(const shared_ptr<ASTNode>& stmt, ofstream& out);
static string evaluateLiteral(const shared_ptr<ASTNode>& node);

// Entry point: converts the AST to simplified C++-like source
void generateCode(const shared_ptr<Function>& func, const string& outputFileName) {
    ofstream out(outputFileName);
    if (!out.is_open()) {
        cerr << "Error: Could not open output file '" << outputFileName << "'\n";
        return;
    }

    out << "int " << func->name << "() {\n";

    for (const auto& stmt : func->body) {
        generateStatement(stmt, out);
    }

    out << "}\n";
    out.close();
}

// Handle a single statement node
static void generateStatement(const shared_ptr<ASTNode>& stmt, ofstream& out) {
    if (auto decl = dynamic_pointer_cast<VariableDeclaration>(stmt)) {
        string value = evaluateLiteral(decl->value);
        out << "  int " << decl->name << " = " << value << ";\n";
    }
    else if (auto ret = dynamic_pointer_cast<ReturnStatement>(stmt)) {
        out << "  return " << ret->return_var << ";\n";
    }
    else {
        out << "  // Unknown statement\n";
    }
}

// Get the value from a Literal node (assumes decl->value is a Literal)
static string evaluateLiteral(const shared_ptr<ASTNode>& node) {
    if (auto lit = dynamic_pointer_cast<Literal>(node)) {
        return lit->value;
    }
    return "0";  // fallback for non-literals (could expand this later)
}

