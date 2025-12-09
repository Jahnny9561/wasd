#include "semantic.h"
#include "lexer.h"
#include "tokens.h"
#include <unordered_set>
#include <iostream>

std::string opToString(int op)
{
    switch (op)
    {
    case opAdd:
        return "ADD";
    case opSub:
        return "SUB";
    case opMult:
        return "MULT";
    case opDiv:
        return "DIV";
    case opPrint:
        return "PRINT";
    case opAssign:
        return "ASSIGN";
    case opInput:
        return "INPUT";
    case opWhile:
        return "WHILE";
    case opBigger:
        return "BIGGER";
    case opSmaller:
        return "SMALLER";
    case opGoTo:
        return "GOTO";
    case opGoToFalse:
        return "GOTO_F";
    case opExit:
        return "Exit";
    default:
        return "?";
    }
}

extern std::unordered_map<std::string, sInfo> symbolTable;
std::vector<semStruct> instructionTable;
int tempCounter = 1;

int getID(std::string name)
{
    if (symbolTable.find(name) != symbolTable.end())
    {
        return symbolTable[name].pos;
    }
    return 0;
}

void updateTable(int p, std::string arg1, std::string arg2, std::string res)
{
    int i1 = 0, i2 = 0, i3 = 0;

    if (p == opGoTo)
    {
        if (arg1 != "-" && arg1 != "PLACEHOLDER")
            i1 = std::stoi(arg1);
    }
    else if (p == opGoToFalse)
    {
        i1 = getID(arg1);
        if (arg2 != "-" && arg2 != "PLACEHOLDER")
            i2 = std::stoi(arg2);
    }
    else
    {
        i1 = getID(arg1);
        i2 = getID(arg2);
        i3 = getID(res);
    }

    instructionTable.push_back({p, i1, i2, i3});
};

std::string newTemp()
{
    std::string tempName = "&" + std::to_string(tempCounter++);

    sInfo info;
    info.pos = counter++;
    info.token = tokenIdentifier;
    info.value = 0;

    symbolTable[tempName] = info;

    return tempName;
}

void printIR()
{
    std::cout << "\n -------- Instruction Table --------\n";
    std::cout << "Op | Arg1 | Arg2 | Res\n";
    for (const auto &row : instructionTable)
    {
        std::cout << opToString(row.op) << "\t"
                  << row.arg1 << "\t"
                  << row.arg2 << "\t"
                  << row.result << "\n";
    }
    std::cout << "----------------------------------------------\n";
}