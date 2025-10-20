#include "lexer.h"
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <cctype>

using namespace std;

// Global variables
unordered_map<string, sInfo> symbolTable;
int counter = 1;

// Sets
unordered_set<string> valid_operands = { "+", "-", "*", "/", "=" };
unordered_set<char> special_symbols = { '(', ')', ',', ';', '_', '{', '}', ':' };

bool isNumber(const string& token) {
    for (char c : token)
        if (!isdigit(c)) return false;
    return true;
}

bool isIdentifier(const string& token) {
    if (token.empty() || !isalpha(token[0])) return false;
    for (size_t i = 1; i < token.length(); ++i)
        if (!isalnum(token[i])) return false;
    return true;
}

tokenType classify(string token) {
    if (token.empty()) return tokenUnknown;
    if (valid_operands.count(token)) return tokenOperand;
    if (isNumber(token)) return tokenNumber;
    if (isIdentifier(token)) return tokenIdentifier;
    if (token.size() == 1 && special_symbols.count(token[0])) return tokenSpecialChar;
    return tokenUnknown;
}

void compare(const string buffer, unordered_map<string, sInfo>& symbolTable, int& counter) {
    auto it = symbolTable.find(buffer);
    if (it == symbolTable.end()) {
        tokenType t = classify(buffer);
        if (t == tokenUnknown) {
            cout << "Error encountered at position: " << counter << endl;
            exit(0);
        }
        symbolTable[buffer] = { counter, t };
        counter++;
    }
}

void tokenize(const string& buffer) {
    string token;
    for (size_t i = 0; i < buffer.length(); ++i) {
        char c = buffer[i];
        if (isspace(c)) {
            if (!token.empty()) { compare(token, symbolTable, counter); token.clear(); }
            continue;
        }
        if (valid_operands.count(string(1, c))) {
            if (!token.empty()) { compare(token, symbolTable, counter); token.clear(); }
            compare(string(1, c), symbolTable, counter);
            continue;
        }
        if (special_symbols.count(c)) {
            if (!token.empty()) { compare(token, symbolTable, counter); token.clear(); }
            compare(string(1, c), symbolTable, counter);
            continue;
        }
        if (isalnum(c)) {
            token += c;
        } else {
            if (!token.empty()) { compare(token, symbolTable, counter); token.clear(); }
            cout << "Unknown character '" << c << "' at position " << i << endl;
        }
    }
    if (!token.empty()) compare(token, symbolTable, counter);
}

string tokenTypeName(int type) {
    switch (type) {
        case tokenOperand: return "Operand";
        case tokenNumber: return "Number";
        case tokenIdentifier: return "Identifier";
        case tokenSpecialChar: return "SpecialChar";
        default: return "Unknown";
    }
}

void listall(const unordered_map<string, sInfo>& table) {
    for (const auto& pair : table)
        cout << pair.second.pos << " | " << pair.first << " | " << tokenTypeName(pair.second.token) << endl;
}
