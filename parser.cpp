#include "parser.h"
#include "tokens.h"
#include "semantic.h"
#include <iostream>
using namespace std;

extern std::vector<StreamToken> tokenStream;

static StreamToken currentToken;
static size_t streamPosition = 0;

static void advanceToken();
static void error(const string &message);
static std::string factor();
static std::string term();
static std::string expr();
static void print_stm();
static void input_stm();
static void assign_stm();
static void while_stm();
static std::string comparison();
static void stm();
static void block();
static void body();
static void head();
static void z();

static void advanceToken()
{

    if (streamPosition >= tokenStream.size())
    {
        currentToken = {"EOF", tokenUnknown};
        return;
    }

    currentToken = tokenStream[streamPosition];
    streamPosition++;
}

void error(const string &message)
{
    string err_msg = "PARSE ERROR: " + message +
                     "\n -> At token: '" + currentToken.lexeme + "'";

    // Throw the error
    throw std::runtime_error(err_msg);
    std::terminate;
}

void z()
{
    head();
    body();
}

void head()
{
    if (currentToken.lexeme != "_")
        error("expected '_'");
    advanceToken();
    if (currentToken.type != 3)
        error("expected ident");
    advanceToken();
    if (currentToken.lexeme != ":")
        error("expected ':'");
    advanceToken();
}

void body()
{
    if (currentToken.lexeme != "{")
        error("expected '{'");
    advanceToken();
    while (currentToken.lexeme != "}" && currentToken.lexeme != "EOF")
    {
        block();
    }
    if (currentToken.lexeme != "}")
        error("expected '}'");
    advanceToken();
}

void block()
{
    if (currentToken.lexeme == "{")
    {
        body();
    }
    else
    {
        stm();
    }
}

void stm()
{
    if (currentToken.lexeme == "print")
        print_stm();
    else if (currentToken.lexeme == "while")
        while_stm();
    else if (currentToken.lexeme == "input")
        input_stm();
    else if (currentToken.type == tokenIdentifier)
        assign_stm();
    else
        error("Statement expected or wrong statement");
}

void assign_stm()
{
    std::string varName = currentToken.lexeme;
    advanceToken();
    if (currentToken.lexeme != "=")
        error("Expected =");
    advanceToken();

    std::string result = expr();

    updateTable(opAssign, result, "-", varName);
}

void input_stm()
{
    advanceToken();
    if (currentToken.type != tokenIdentifier)
        error("Identifier expected");
    std::string varName = currentToken.lexeme;
    updateTable(opInput, "-", "-", varName);
    advanceToken();
}

void print_stm()
{
    advanceToken();
    std::string result = expr();
    updateTable(opPrint, result, "-", "-");
}

void while_stm()
{
    advanceToken();
    std::string startLabel = std::to_string(instructionTable.size());
    std::string condResult = comparison();

    int jumpInstructionIndex = instructionTable.size();
    updateTable(opGoToFalse, condResult, "-", "-");

    if (currentToken.lexeme != ":")
        error("':' expected");
    advanceToken();
    body();
    updateTable(opGoTo, startLabel, "-", "-");
    std::string endLabel = std::to_string(instructionTable.size());
    instructionTable[jumpInstructionIndex].arg2 = std::stoi(endLabel);
}

std::string comparison()
{
    std::string left = expr();

    if (currentToken.lexeme == "<" || currentToken.lexeme == ">")
    {
        string op = currentToken.lexeme;
        advanceToken();

        std::string right = expr();
        std::string temp = newTemp();

        int opcode = (op == "<") ? opSmaller : opBigger;

        updateTable(opcode, left, right, temp);

        return temp;
    }
    else
    {
        return left;
    }
}

std::string expr()
{
    std::string left = term();

    while (currentToken.lexeme == "+")
    {
        advanceToken();
        std::string right = term();
        std::string temp = newTemp();

        updateTable(opAdd, left, right, temp);
        left = temp;
    }
    return left;
}

std::string term()
{
    std::string left = factor();

    while (currentToken.lexeme == "*")
    {
        advanceToken();
        std::string right = factor();
        std::string temp = newTemp();

        updateTable(opMult, left, right, temp);
        left = temp;
    }
    return left;
}

std::string factor()
{
    std::string result = "";
    if (currentToken.type == tokenIdentifier)
    {
        result = currentToken.lexeme;
        advanceToken();
    }
    else if (currentToken.type == tokenNumber)
    {
        result = currentToken.lexeme;
        advanceToken();
    }
    else if (currentToken.lexeme == "(")
    {
        advanceToken();
        result = expr();
        if (currentToken.lexeme != ")")
            error("Expected ')'");
        advanceToken();
    }
    else
    {
        error("Expected identifier, number, or '('");
    }
    return result;
}

bool parser()
{
    cout << "--- Parser Start ---" << endl;
    try
    {
        advanceToken();
        while (currentToken.lexeme != "EOF")
        {
            z();
        }

        updateTable(opExit, "-", "-", "-");
        cout << "--- Parser End Successfully ---" << endl;
        return true;
    }
    catch (const std::runtime_error &e)
    {
        // Print the error message
        cout << e.what() << endl;

        return false;
    }
}