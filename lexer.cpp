#include "lexer.h"
#include <iostream>
#include <regex>
#include <cctype>

// List of keywords
const std::vector<std::string> keywords = {
    "if", "else", "while", "return", "int", "float", "char", "void"
};

// Constructor
Lexer::Lexer(const std::string& source_code)
    : source_code(source_code), current_pos(0), current_line(1) {
    current_char = source_code.empty() ? '\0' : source_code[0];
}

void Lexer::advance() {
    if (current_char == '\n') {
        current_line++;
    }
    current_pos++;
    if (current_pos < source_code.size()) {
        current_char = source_code[current_pos];
    } else {
        current_char = '\0';  // EOF
    }
}

void Lexer::skip_whitespace() {
    while (isspace(current_char)) {
        advance();
    }
}

void Lexer::skip_comment() {
    // Skip until end of line
    while (current_char != '\0' && current_char != '\n') {
        advance();
    }
}

Token Lexer::identifier_or_keyword() {
    std::string value;
    while (isalnum(current_char) || current_char == '_') {
        value += current_char;
        advance();
    }
    // Check if it's a keyword
    for (const auto& keyword : keywords) {
        if (value == keyword) {
            return {KEYWORD, value, current_line};
        }
    }
    return {IDENTIFIER, value, current_line};
}

Token Lexer::number() {
    std::string value;
    while (isdigit(current_char)) {
        value += current_char;
        advance();
    }
    return {NUMBER, value, current_line};
}

Token Lexer::operator_token() {
    std::string value;
    if (current_char == '+' || current_char == '-' ||
        current_char == '*' || current_char == '/' ||
        current_char == '=' || current_char == '<' || current_char == '>') {
        value += current_char;
        advance();
    }
    return {OPERATOR, value, current_line};
}

Token Lexer::punctuation() {
    std::string value;
    value += current_char;
    advance();
    return {PUNCTUATION, value, current_line};
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (current_char != '\0') {
        if (isspace(current_char)) {
            skip_whitespace();
        } else if (current_char == '/' && source_code[current_pos + 1] == '/') {
            advance(); // skip '/'
            advance(); // skip second '/'
            skip_comment();
        } else if (isalpha(current_char) || current_char == '_') {
            tokens.push_back(identifier_or_keyword());
        } else if (isdigit(current_char)) {
            tokens.push_back(number());
        } else if (current_char == '+' || current_char == '-' ||
                   current_char == '*' || current_char == '/' ||
                   current_char == '=' || current_char == '<' ||
                   current_char == '>') {
            tokens.push_back(operator_token());
        } else if (current_char == ';' || current_char == '(' ||
                   current_char == ')' || current_char == '{' ||
                   current_char == '}' || current_char == ',') {
            tokens.push_back(punctuation());
        } else {
            std::cerr << "Unexpected character: " << current_char
                      << " at line " << current_line << std::endl;
            advance();
        }
    }
    tokens.push_back({EOF_TOKEN, "", current_line});
    return tokens;
}
