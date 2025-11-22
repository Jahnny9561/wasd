#include "semantic.h"
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
    default:
        return "?";
    }
}

std::vector<semStruct> instructionTable;
int tempCounter = 1;

void updateTable(int p, std::string arg1, std::string arg2, std::string res)
{
    instructionTable.push_back({p, arg1, arg2, res});
};

std::string newTemp()
{
    return "&" + std::to_string(tempCounter++);
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