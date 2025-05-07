#ifndef CODEGEN_H
#define CODEGEN_H

#include <string>
#include <memory>
#include "ast.h" 



void generateCode(const std::shared_ptr<Function>& func, const std::string& outputFileName);

#endif 
