// lexer.h
#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

using namespace std;

enum TokenType {
    KEYWORD, IDENTIFIER, OPERATOR, NUMBER, PUNCTUATION, EOF_TOKEN
};

struct Token {
    TokenType type;
    string value;
    int line_number;
};

class Lexer {
public:
    Lexer(const string& source_code);
    vector<Token> tokenize();
private:
    string source_code;
    int current_pos;
    int current_line;
    char current_char;
    void advance();
    void skip_whitespace();
    void skip_comment();
    Token identifier_or_keyword();
    Token number();
    Token operator_token();
    Token punctuation();
};

#endif // LEXER_H