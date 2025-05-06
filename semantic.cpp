#include "semantic.h"
#include <iostream>

SemanticAnalyzer::SemanticAnalyzer() {}

void SemanticAnalyzer::declareVariable(const std::string& name, const std::string& type) {
    if (symbolTable.find(name) != symbolTable.end()) {
        semanticErrors.push_back("Semantic error: Variable '" + name + "' is already declared.");
        return;
    }
    symbolTable[name] = { type, false };
}

void SemanticAnalyzer::assignVariable(const std::string& name) {
    if (symbolTable.find(name) == symbolTable.end()) {
        semanticErrors.push_back("Semantic error: Variable '" + name + "' used before declaration.");
        return;
    }
    symbolTable[name].initialized = true;
}

bool SemanticAnalyzer::isDeclared(const std::string& name) const {
    return symbolTable.find(name) != symbolTable.end();
}

void SemanticAnalyzer::checkReturnType(const std::string& function, const std::string& actualType) {
    if (function == "main" && actualType != "int") {
        semanticErrors.push_back("Semantic error: Function 'main' must return int.");
    }

}

void SemanticAnalyzer::printSemanticErrors() const {
    for (const std::string& err : semanticErrors) {
        std::cout << err << std::endl;
    }
}

bool SemanticAnalyzer::hasErrors() const {
    return !semanticErrors.empty();
}
