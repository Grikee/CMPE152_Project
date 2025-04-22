<<<<<<< HEAD
#include <iostream>
using namespace std;
=======
#include<iostream>
#include<fstream>
#include<string>
#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "semantic.h"
#include "codegen.h"
#include "error.h"
>>>>>>> 74bb60c (tasks.json, test case 1, testing command, compiler_test executable, settings.json, file read testing in main file.)

using namespace std;

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

  string line;
  while (getline(file, line)) {
      cout << line << endl;
  }
  //ifstream file()
  return 0;
}
