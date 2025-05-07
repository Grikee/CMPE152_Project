#include "parser.h"
#include "ast.h"
#include "utils.h"
#include <iostream>
#include<unordered_set>

using namespace std;


string token_type_to_string(TokenType type) {  // <-- define the helper function
    switch (type) {
        case KEYWORD: return "KEYWORD";
        case IDENTIFIER: return "IDENTIFIER";
        case PUNCTUATION: return "PUNCTUATION";
        case OPERATOR: return "OPERATOR";
        case NUMBER: return "NUMBER";
        default: return "UNKNOWN";
    }
}

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
        // Missing semicolon
        if (type == PUNCTUATION && current_token.value != ";") {
            cerr << "Syntax error: Expected ';' but got '" << current_token.value << "' on line " << current_token.line_number << endl;
        } else {
            cerr << "Syntax error: Expected token type '" << token_type_to_string(type) << "' but got '" << current_token.value << "' on line " << current_token.line_number << endl;
        }
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

shared_ptr<ASTNode> Parser::parse() {
    auto root = make_shared<Function>("main");
    
    match(KEYWORD, "int");  // match int keyword for function return type
    match(IDENTIFIER, "main"); // match 'main' function name
    match(PUNCTUATION, "(");
    match(PUNCTUATION, ")");
    match(PUNCTUATION, "{");

    // Create a symbol table to track declared variables
    unordered_set<string> declared_variables;

    while (current_token.type != PUNCTUATION || current_token.value != "}") {
        if (current_token.type == KEYWORD && current_token.value == "int") {
            match(KEYWORD, "int");
            string var_name = current_token.value;
            match(IDENTIFIER);  // get variable name
            match(OPERATOR, "=");
            
            string expr_value;
            while (current_token.type != PUNCTUATION || current_token.value != ";") {
                expr_value += current_token.value + " ";
                advance();
            }
            match(PUNCTUATION, ";");  // expect semicolon at the end

            declared_variables.insert(var_name); // mark variable as declared

            auto literal_node = make_shared<Literal>(expr_value);
            auto var_decl_node = make_shared<VariableDeclaration>(var_name, literal_node);
            root->add_statement(var_decl_node);

        } else if (current_token.type == KEYWORD && current_token.value == "return") {
            match(KEYWORD, "return");
            string return_var = current_token.value;
            match(IDENTIFIER);

            // Check if variable used in return is declared
            if (declared_variables.find(return_var) == declared_variables.end()) {
                cerr << "Semantic error: Variable '" << return_var << "' used before declaration." << endl;
                exit(1);
            }

            match(PUNCTUATION, ";");  // expect semicolon at the end

            auto return_node = make_shared<ReturnStatement>(return_var);
            root->add_statement(return_node);
        } else {
            cerr << "Syntax error: Invalid statement at line " << current_token.line_number << endl;
            exit(1);
        }
    }

    match(PUNCTUATION, "}");  // closing brace
    return root;
}


void Parser::parse_statement() {
    if (current_token.type == KEYWORD && current_token.value == "int") {
        if (tokens.size() > current_token_idx + 1 &&
            tokens[current_token_idx + 1].type == IDENTIFIER &&
            tokens[current_token_idx + 1].value == "main") {
            parse_function_definition(); // Handle function definition
        } else {
            // Variable declaration
            match(KEYWORD, "int");
            string var_name = current_token.value;
            match(IDENTIFIER);
            match(OPERATOR, "=");
            string literal_value = current_token.value;
            match(NUMBER);
            match(PUNCTUATION, ";");

            auto literal_node = make_shared<Literal>(literal_value);
            auto var_decl_node = make_shared<VariableDeclaration>(var_name, literal_node);
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


