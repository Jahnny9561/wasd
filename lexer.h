#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <unordered_map>
#include "tokens.h"

extern std::unordered_map<std::string, sInfo> symbolTable;
extern int counter;

void tokenize(const std::string& buffer);
void listall(const std::unordered_map<std::string, sInfo>& table);
void compare(const std::string buffer, std::unordered_map<std::string, sInfo>& symbolTable, int& counter);
tokenType classify(std::string token);
bool isNumber(const std::string& token);
bool isIdentifier(const std::string& token);

#endif
