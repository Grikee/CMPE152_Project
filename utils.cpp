// utils.cpp
#include "utils.h"
using namespace std;

string token_type_to_string(TokenType type) {
    switch (type) {
        case KEYWORD: return "KEYWORD";
        case IDENTIFIER: return "IDENTIFIER";
        case PUNCTUATION: return "PUNCTUATION";
        case OPERATOR: return "OPERATOR";
        case NUMBER: return "NUMBER";
        default: return "UNKNOWN";
    }
}
