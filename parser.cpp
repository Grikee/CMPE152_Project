#include "parser.h"
#include <iostream>

using namespace std;

Parser::Parser(vector<Token>& tokens) : tokens(tokens), current_token_idx(0) {
    current_token = tokens[current_token_idx];
}

void Parser::advance() {
    current_token_idx++;
    if (current_token_idx < tokens.size()) {
        current_token = tokens[current_token_idx];
    }
}

void Parser::match(TokenType type) {
    if (current_token.type == type) {
        advance();
    } else {
        cerr << "Syntax error: Expected token type but got '" << current_token.value << "' on line " << current_token.line_number << endl;
        exit(1);
    }
}

void Parser::match(TokenType type, const string& value) {
    if (current_token.type == type && current_token.value == value) {
        advance();
    } else {
        cerr << "Syntax error: Expected '" << value << "' but got '" << current_token.value << "' on line " << current_token.line_number << endl;
        exit(1);
    }
}

void Parser::parse() {
    while (current_token.type != EOF_TOKEN) {
        parse_statement();
    }
}

void Parser::parse_statement() {
    if (current_token.type == KEYWORD && current_token.value == "int") {
        // Check if it's the start of a function definition without advancing
        if (tokens.size() > current_token_idx + 1 &&
            tokens[current_token_idx + 1].type == IDENTIFIER &&
            tokens[current_token_idx + 1].value == "main") {
            parse_function_definition(); // Let it handle all matching
        } else {
            // Variable declaration
            match(KEYWORD, "int");
            match(IDENTIFIER);
            match(OPERATOR, "=");
            match(NUMBER);
            match(PUNCTUATION, ";");
        }
    } else if (current_token.type == KEYWORD && current_token.value == "return") {
        parse_return_statement();
    } else {
        cerr << "Syntax error: Invalid statement at line " << current_token.line_number << endl;
        exit(1);
    }
}

void Parser::parse_function_definition() {
    cout << "Parsing function definition..." << endl;
    match(KEYWORD, "int");
    match(IDENTIFIER, "main");
    match(PUNCTUATION, "(");
    match(PUNCTUATION, ")");
    match(PUNCTUATION, "{");

    while (current_token.type != PUNCTUATION || current_token.value != "}") {
        parse_statement();
    }

    match(PUNCTUATION, "}");
}


void Parser::parse_return_statement() {
    match(KEYWORD, "return");
    match(IDENTIFIER);           // Handle the identifier that comes after return
    match(PUNCTUATION, ";");     // End of the return statement
}

void Parser::parse_expression() {
    match(IDENTIFIER);
    match(OPERATOR);
    match(NUMBER);
    match(PUNCTUATION, ";");
}

void Parser::parse_block() {
    match(PUNCTUATION, "{");
    while (current_token.type != PUNCTUATION || current_token.value != "}") {
        parse_statement();
    }
    match(PUNCTUATION, "}");
}
