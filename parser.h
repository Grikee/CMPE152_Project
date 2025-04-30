#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "lexer.h"

using namespace std;

class Parser {
public:
    Parser(vector<Token>& tokens);
    void parse();
private:
    vector<Token> tokens;
    int current_token_idx;
    Token current_token;
    
    void advance();
    void match(TokenType type);
    void match(TokenType type, const string& value);

    void parse_statement();
    void parse_expression();
    void parse_function_definition();
    void parse_return_statement();
    void parse_block();
};

#endif // PARSER_H
