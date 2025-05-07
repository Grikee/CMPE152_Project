#include "codegen.h"
#include <fstream>
#include <sstream>
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


#include <sstream>

static string evaluateLiteral(const shared_ptr<ASTNode>& node) {
    if (auto lit = dynamic_pointer_cast<Literal>(node)) {
        return lit->value;
    }
    else if (auto bin = dynamic_pointer_cast<BinaryExpression>(node)) {
        string lhsStr = evaluateLiteral(bin->lhs);
        string rhsStr = evaluateLiteral(bin->rhs);

        
        try {
            int lhs = stoi(lhsStr);
            int rhs = stoi(rhsStr);
            int result = 0;

            if (bin->op == "+") result = lhs + rhs;
            else if (bin->op == "-") result = lhs - rhs;
            else if (bin->op == "*") result = lhs * rhs;
            else if (bin->op == "/") result = rhs != 0 ? lhs / rhs : 0;

            return to_string(result);
        }
        catch (...) {
            
            return lhsStr + " " + bin->op + " " + rhsStr;
        }
    }

    return "0";  
}

