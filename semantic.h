#ifndef SEMANTIC_H
#define SEMANTIC_H

#include <string>
#include <unordered_map>
#include <vector>


using namespace std;

struct VariableInfo {
   string type;
   bool initalized;
};

class SemanticAnalyzer {

public:
    SemanticAnalyzer();

    void declareVariable(const string& name, const string& type);
    void assignVariable(const string& name);
    bool isDeclared(const string& name) const;

    void checkReturnType(const string& function, const string& actualType);

    void printSemanticErrors() const;
    bool hasErrors() const;
};

#endif

