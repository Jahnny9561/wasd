#include "parser.h"
#include "tokens.h"
#include <iostream>
using namespace std;

extern std::vector<StreamToken> tokenStream;

static StreamToken currentToken;
static size_t streamPosition = 0;

static void advanceToken();
static void error(const string& message);
static void factor();
static void term();
static void expr();
static void print_stm();
static void input_stm();
static void assign_stm();
static void while_stm();
static void comparison();
static void stm();
static void block();
static void body();
static void head();
static void z();

static void advanceToken() {

    if (streamPosition >= tokenStream.size()) {
        currentToken = { "EOF", tokenUnknown };
        return;
    }

    currentToken = tokenStream[streamPosition];
    streamPosition++;
}

void error(const string& message){
    string err_msg = "PARSE ERROR: " + message + 
                     "\n -> At token: '" + currentToken.lexeme + "'";
    
    //Throw the error 
    throw std::runtime_error(err_msg);
    std::terminate;
}

void z(){
    head();
    body();
}

void head(){
 if ( currentToken.lexeme != "_" )  error("expected '_'"); 
 advanceToken();
 if ( currentToken.type != 3 )  error("expected ident"); 
 advanceToken();
 if ( currentToken.lexeme != ":" )  error("expected ':'"); 
 advanceToken();
}

void body(){
if (currentToken.lexeme != "{") error("expected '{'");
advanceToken();
while (currentToken.lexeme != "}" && currentToken.lexeme != "EOF") {
        block();
    }
if (currentToken.lexeme != "}") error ("expected '}'");
advanceToken();
}

void block(){
        if (currentToken.lexeme == "{") {
        body();
    } else {
        stm();
    }
}

void stm(){
    if (currentToken.lexeme == "print") print_stm();
    else if (currentToken.lexeme == "while") while_stm();
    else if (currentToken.lexeme == "input") input_stm();
    else if (currentToken.type == 3) assign_stm();
    else error("Statement expected or wrong statement");
}

void assign_stm(){
    advanceToken();
    if (currentToken.lexeme != "=") error("Expected =");
    advanceToken();
    comparison();
}

void input_stm(){
    advanceToken();
    if (currentToken.type != tokenIdentifier) error("Identifier expected");
    advanceToken();
}

void print_stm(){
    advanceToken();
        
    comparison();
}

void while_stm(){
    advanceToken();
    comparison();
    if (currentToken.lexeme != ":") error("':' expected");
    advanceToken();
    body();
}

void comparison(){
    expr();

    if (currentToken.lexeme == "<" || currentToken.lexeme == ">") 
    {
        advanceToken();
        expr();
    }
}

void expr(){
    term();

    while (currentToken.lexeme == "+"){
        advanceToken();
        term();
    }
}

void term(){
    factor();

    while (currentToken.lexeme == "*"){
        advanceToken();
        factor();
    }
}

void factor(){
    if (currentToken.type == tokenIdentifier){
        advanceToken();
    }
    else if (currentToken.type == tokenNumber){
        advanceToken();
    }
    else if (currentToken.lexeme == "("){
        advanceToken(); 
        comparison(); 

        if (currentToken.lexeme != ")") error ("Expected ')'");
        advanceToken();
    }
    else {
        error("Expected identifier, number, or '('");   
    }
}

bool parser(){
    cout << "--- Parser Start ---" << endl;
    try{    
        advanceToken();
        while (currentToken.lexeme != "EOF") {
            z();
            }
            cout << "--- Parser End Successfully ---" << endl;
            return true;
    }
    catch (const std::runtime_error& e) {
        // Print the error message
        cout << e.what() << endl;

        return false;
    }
}