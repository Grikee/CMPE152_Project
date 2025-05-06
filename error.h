#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <vector>


extern int errorCount;


void reportError(const std::string& message);


void reportSyntaxError(int line, const std::string& message);


void reportSemanticError(int line, const std::string& message);


bool hasErrors();


void printAllErrors();

#endif 
