#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

// Abstract base class for all AST nodes
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void print(int indent = 0) const = 0;
};

// Utility function (used internally in .cpp)
void print_indent(int indent);

// Literal node: represents a constant value
class Literal : public ASTNode {
public:
    string value;

    Literal(const string& val);
    void print(int indent = 0) const override;
};


class BinaryExpression : public ASTNode {
    public:
        string op;  // "+", "-", "*", "/"
        shared_ptr<ASTNode> lhs;
        shared_ptr<ASTNode> rhs;
    
        BinaryExpression(const string& op, shared_ptr<ASTNode> lhs, shared_ptr<ASTNode> rhs);
        void print(int indent = 0) const override;
    };
    

// VariableDeclaration node: represents "int x = 5;"
class VariableDeclaration : public ASTNode {
public:
    string name;
    shared_ptr<ASTNode> value;

    VariableDeclaration(const string& name, shared_ptr<ASTNode> value);
    void print(int indent = 0) const override;
};

// ReturnStatement node: represents "return x;"
class ReturnStatement : public ASTNode {
public:
    string return_var;

    ReturnStatement(const string& var_name);
    void print(int indent = 0) const override;
};

// Function node: represents "int main() { ... }"
class Function : public ASTNode {
public:
    string name;
    vector<shared_ptr<ASTNode>> body;

    Function(const string& name);
    void add_statement(shared_ptr<ASTNode> stmt);
    void print(int indent = 0) const override;
};

#endif // AST_H
