#include "codegen.h"
#include <fstream>
#include <iostream>

static std::ofstream outFile;

void initCodeGen(const std::string& outputFileName) {
    outFile.open(outputFileName);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open output file: " << outputFileName << std::endl;
        exit(1);
    }
}

void finalizeCodeGen() {
    if (outFile.is_open()) {
        outFile.close();
    }
}

void generateStatement(const StatementNode* stmt);
void generateExpression(const ExpressionNode* expr);


void generateCode(const ProgramNode* program) {
    for (const auto& stmt : program->statements) {
        generateStatement(stmt);
    }
}


void generateStatement(const StatementNode* stmt) {
    switch (stmt->type) {
        case StatementType::Declaration:
            outFile << stmt->variableType << " " << stmt->variableName << ";" << std::endl;
            break;
        case StatementType::Assignment:
            outFile << stmt->variableName << " = ";
            generateExpression(stmt->expression);
            outFile << ";" << std::endl;
            break;
        case StatementType::Return:
            outFile << "return ";
            generateExpression(stmt->expression);
            outFile << ";" << std::endl;
            break;
   
        default:
            std::cerr << "Error: Unknown statement type." << std::endl;
            break;
    }
}


void generateExpression(const ExpressionNode* expr) {
    switch (expr->type) {
        case ExpressionType::IntegerLiteral:
            outFile << expr->intValue;
            break;
        case ExpressionType::Variable:
            outFile << expr->variableName;
            break;
        case ExpressionType::BinaryOperation:
            outFile << "(";
            generateExpression(expr->left);
            outFile << " " << expr->operatorSymbol << " ";
            generateExpression(expr->right);
            outFile << ")";
            break;

        default:
            std::cerr << "Error: Unknown expression type." << std::endl;
            break;
    }
}
