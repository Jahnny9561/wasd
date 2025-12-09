#include "interpreter.h"
#include "semantic.h"
#include "lexer.h"
#include "tokens.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

static vector<int> memory;

void initMemory()
{
    memory.assign(counter + 1, 0);

    for (const auto &pair : symbolTable)
    {
        string lexeme = pair.first;
        sInfo info = pair.second;

        if (info.token == tokenNumber)
        {
            memory[info.pos] = stoi(lexeme);
        }
    }
}

void runProgram()
{
    cout << "\n--- PROGRAM OUTPUT ---\n";
    initMemory();

    // Intruction pointer
    int ip = 0;

    while (ip < instructionTable.size())
    {
        const semStruct &instr = instructionTable[ip];

        // Based on the OpCode, do the work
        switch (instr.op)
        {
        case opAdd:
            memory[instr.result] = memory[instr.arg1] + memory[instr.arg2];
            break;

        case opSub:
            memory[instr.result] = memory[instr.arg1] - memory[instr.arg2];
            break;

        case opMult:
            memory[instr.result] = memory[instr.arg1] * memory[instr.arg2];
            break;

        case opDiv:
            if (memory[instr.arg2] == 0)
            {
                cerr << "Runtime Error: Division by Zero!" << endl;
                return;
            }
            memory[instr.result] = memory[instr.arg1] / memory[instr.arg2];
            break;

        case opAssign:
            memory[instr.result] = memory[instr.arg1];
            break;

        case opInput:
            cout << "Input value: ";
            cin >> memory[instr.result];
            break;

        case opPrint:
            cout << memory[instr.arg1] << endl;
            break;

        case opSmaller: //<
            // Store 1 if true, 0 if false
            memory[instr.result] = (memory[instr.arg1] < memory[instr.arg2]) ? 1 : 0;
            break;

        case opBigger: // >
            memory[instr.result] = (memory[instr.arg1] > memory[instr.arg2]) ? 1 : 0;
            break;

            // ---jumps

        case opGoTo:
            ip = instr.arg1;
            continue;

        case opGoToFalse:
            if (memory[instr.arg1] == 0)
            {
                ip = instr.arg2;
                continue;
            }
            break;

        case opExit:
            cout << "--- EXIT INSTRUCTION REACHED ---" << endl;
            return;
        default:
            cerr << "Runtime Error: Unknown OpCode " << instr.op << endl;
            return;
        }
        ip++;
    }
    cout << "--- END OF PROGRAM ---\n";
}
