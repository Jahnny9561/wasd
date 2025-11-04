#ifndef TOKENS_H
#define TOKENS_H

#include <string>

enum tokenType {
    tokenUnknown,     // 0
    tokenOperand,     // 1
    tokenNumber,      // 2
    tokenIdentifier,  // 3
    tokenSpecialChar  // 4
};

struct sInfo {
    int pos;
    int token;
};

struct StreamToken {
    std::string lexeme;
    tokenType type;
};

#endif
