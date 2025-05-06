#include "error.h"
#include <iostream>


int errorCount = 0;


static std::vector<std::string> errorMessages;


void reportError(const std::string& message) {
    errorMessages.push_back("Error: " + message);
    ++errorCount;
}


void reportSyntaxError(int line, const std::string& message) {
    errorMessages.push_back("Syntax Error (Line " + std::to_string(line) + "): " + message);
    ++errorCount;
}


void reportSemanticError(int line, const std::string& message) {
    errorMessages.push_back("Semantic Error (Line " + std::to_string(line) + "): " + message);
    ++errorCount;
}


bool hasErrors() {
    return errorCount > 0;
}


void printAllErrors() {
    for (const auto& msg : errorMessages) {
        std::cerr << msg << std::endl;
    }
}
