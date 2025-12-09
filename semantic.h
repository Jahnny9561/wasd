#ifndef SEMANTIC_H
#define SEMANTIC_H

#include <string>
#include <vector>

enum operation
{
    opAdd = 1,  // +
    opSub = 2,  // -
    opMult = 3, // *
    opDiv = 4,  // /
    opPrint = 5,
    opAssign = 6,
    opInput = 7,
    opWhile = 8,
    opBigger = 9, // >
    opSmaller = 10,
    opGoTo = 11,
    opGoToFalse = 12,
    opExit = 13
};

// Semantic struct for quadruples
struct semStruct
{
    int op;
    int arg1;
    int arg2;
    int result;
};

// Global variable for the instruction table
extern std::vector<semStruct> instructionTable;

// Function to add a new instruction
void updateTable(int op, std::string arg1, std::string arg2, std::string result);

// Makes temp variable
std::string newTemp();

// prints the instruction table
void printIR();

#endif