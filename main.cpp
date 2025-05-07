#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "semantic.h"
#include "codegen.h"
#include "error.h"

using namespace std;

//1
//token_type_to_string, lexer_test
string token_type_to_string(TokenType type){
  switch (type) {
    case KEYWORD: return "KEYWORD";
    case IDENTIFIER: return "IDENTIFIER";
    case OPERATOR: return "OPERATOR";
    case NUMBER: return "NUMBER";
    case PUNCTUATION: return "PUNCTUATION";
    case EOF_TOKEN: return "EOF";
    default: return "UNKNOWN";
  }
}

int main(int argc, char* argv[]){
  //check if a file is provided
  if(argc < 2){
    cerr << "Error: No source code provided. " << endl;
    return 1;
  }
   
  // Read source code from file
  ifstream file(argv[1]);
  if (!file.is_open()) {
    cerr << "Error: Could not open file " << argv[1] << endl;
    return 1;
  }

  stringstream buffer;
  buffer << file.rdbuf();
  string source_code = buffer.str();
  file.close();

  //1
  Lexer lexer(source_code);
  vector<Token> tokens = lexer.tokenize();

  //Token types, lexer_test
  //Debugging
  // for (const auto& token : tokens){
  //   cout << "Type: " << token_type_to_string(token.type)
  //     << ", Value: '" << token.value
  //     << "', Line: " << token.line_number << endl;
  // }

  //2
  cout << "Parsing..." << endl;
  Parser parser(tokens);
  // parser.parse();
  shared_ptr<ASTNode> ast = parser.parse();
  //Debugging
  // ast->print();

  // Semantic Analysis   
  SemanticAnalyzer semanticAnalyzer;
  semanticAnalyzer.declareVariable("main", "int");
  if (auto func = dynamic_pointer_cast<Function>(ast)) {
    for (const auto& stmt : func->body) {
      if (auto decl = dynamic_pointer_cast<VariableDeclaration>(stmt)) {
        semanticAnalyzer.declareVariable(decl->name, "int");
      } else if (auto ret = dynamic_pointer_cast<ReturnStatement>(stmt)) {
      if (!semanticAnalyzer.isDeclared(ret->return_var)) {
        reportSemanticError(0, "Undeclared variable: " + ret->return_var);
        }
      }
    }
  }

// Check for semantic errors
if (semanticAnalyzer.hasErrors()) {
  semanticAnalyzer.printSemanticErrors();
  return 1;
}

// Code Generation
cout << "Generating code..." << endl;
generateCode(dynamic_pointer_cast<Function>(ast), "output.cpp");
cout << "Code generated successfully in 'output.cpp'." << endl;

// Print all errors if any
if (hasErrors()) {
  printAllErrors();
  return 1;
}

  return 0;
}
