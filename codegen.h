#ifndef CODEGEN_H
#define CODEGEN_H

#include <string>
#include "ast.h" 


void initCodeGen(const std::string& outputFileName);


void finalizeCodeGen();


void generateCode(const ProgramNode* program);

#endif 
