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
//token_type_to_string, lexer.cpp test
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

  Lexer lexer(source_code);
  vector<Token> tokens = lexer.tokenize();

  for (const auto& token : tokens){
    cout << "Type: " << token_type_to_string(token.type)
      << ", Value: '" << token.value
      << "', Line: " << token.line_number << endl;
  }

  return 0;
}
