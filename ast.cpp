#include "ast.h"
using namespace std;

void print_indent(int indent) {
    for (int i = 0; i < indent; ++i) cout << "  ";
}

// ----- Literal -----
Literal::Literal(const string& val) : value(val) {}

void Literal::print(int indent) const {
    print_indent(indent);
    cout << "Literal: " << value << endl;
}

// ----- VariableDeclaration -----
VariableDeclaration::VariableDeclaration(const string& name, shared_ptr<ASTNode> value)
    : name(name), value(std::move(value)) {}

void VariableDeclaration::print(int indent) const {
    print_indent(indent);
    cout << "VariableDeclaration: " << name << endl;
    value->print(indent + 1);
}

// ----- ReturnStatement -----
ReturnStatement::ReturnStatement(const string& var_name)
    : return_var(var_name) {}

void ReturnStatement::print(int indent) const {
    print_indent(indent);
    cout << "Return: " << return_var << endl;
}

// ----- Function -----
Function::Function(const string& name)
    : name(name) {}

void Function::add_statement(shared_ptr<ASTNode> stmt) {
    body.push_back(std::move(stmt));
}

void Function::print(int indent) const {
    print_indent(indent);
    cout << "Function: " << name << endl;
    for (const auto& stmt : body) {
        stmt->print(indent + 1);
    }
}

// ----- BinaryExpression -----
BinaryExpression::BinaryExpression(const string& op,
    shared_ptr<ASTNode> lhs,
    shared_ptr<ASTNode> rhs)
: op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}

void BinaryExpression::print(int indent) const {
print_indent(indent);
cout << "BinaryExpression: " << op << endl;
lhs->print(indent + 1);
rhs->print(indent + 1);
}

