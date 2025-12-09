#include "interpreter.h"
#include "semantic.h"
#include "lexer.h"
#include "tokens.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>

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

string getName(int id)
{
    for (const auto &pair : symbolTable)
    {
        if (pair.second.pos == id)
            return pair.first;
    }
    return "-1";
}

string getArgName(int id)
{
    if (id <= 0)
        return "-";
    return getName(id);
}

string getArgInfo(int id)
{
    if (id <= 0)
        return "-";

    for (const auto &pair : symbolTable)
    {
        if (pair.second.pos == id)
        {
            string name = pair.first;

            if (pair.second.token == tokenNumber)
            {
                return name;
            }

            string valStr = "-";
            if (id < memory.size())
            {
                valStr = to_string(memory[id]);
            }
            return name + " = " + valStr;
        }
    }
    return "-";
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

void debugProgram()
{
    initMemory();
    int ip = 0;
    cin.ignore();

    while (ip < instructionTable.size())
    {
        const semStruct &instr = instructionTable[ip];

        system("cls");

        cout << "========================================================\n";
        cout << "                WASD TRACE DEBUGGER                     \n";
        cout << "========================================================\n\n";

        cout << "  Current Line: " << ip << "\n";
        cout << "  Instruction : " << opToString(instr.op) << "\n\n";

        cout << "  +----------------------+----------------------+----------------------+\n";
        cout << "  | ARG 1 (Val)          | ARG 2 (Val)          | RESULT (Dest)        |\n";
        cout << "  +----------------------+----------------------+----------------------+\n";
        cout << "  | " << left << setw(20) << getArgInfo(instr.arg1)
             << " | " << setw(20) << getArgInfo(instr.arg2)
             << " | " << setw(20) << getArgName(instr.result) << " |\n";
        cout << "  +----------------------+----------------------+----------------------+\n\n";

        cout << "  > Press ENTER to step...";
        cin.get();

        // save old value
        int targetID = instr.result;
        int oldVal = 0;
        if (targetID > 0 && targetID < memory.size())
        {
            oldVal = memory[targetID];
        }

        // execute code
        bool jumped = false;
        cout << "\n  --------------------------------------------------------\n";

        switch (instr.op)
        {
        case opAdd:
            memory[targetID] = memory[instr.arg1] + memory[instr.arg2];
            break;
        case opSub:
            memory[targetID] = memory[instr.arg1] - memory[instr.arg2];
            break;
        case opMult:
            memory[targetID] = memory[instr.arg1] * memory[instr.arg2];
            break;
        case opDiv:
            if (memory[instr.arg2] == 0)
            {
                cout << "  [ERROR] Division by zero!\n";
                return;
            }
            memory[targetID] = memory[instr.arg1] / memory[instr.arg2];
            break;
        case opAssign:
            memory[targetID] = memory[instr.arg1];
            break;

        case opSmaller:
            memory[targetID] = (memory[instr.arg1] < memory[instr.arg2]);
            break;
        case opBigger:
            memory[targetID] = (memory[instr.arg1] > memory[instr.arg2]);
            break;

        case opInput:
            cout << "  [INPUT] Enter value for " << getArgName(targetID) << ": ";
            cin >> memory[targetID];
            cin.ignore();
            break;

        case opPrint:
            cout << "  [OUTPUT] " << memory[instr.arg1] << endl;
            break;

        case opGoTo:
            ip = instr.arg1;
            jumped = true;
            cout << "  >>> JUMPING to Line " << ip << endl;
            break;

        case opGoToFalse:
        {
            int condVal = memory[instr.arg1];
            if (condVal == 0)
            {
                ip = instr.arg2;
                jumped = true;
                cout << "  >>> Condition is FALSE (0). Jumping to Line " << ip << endl;
            }
            else
            {
                cout << "  >>> Condition is TRUE (" << condVal << "). Continuing." << endl;
            }
            break;
        }
        case opExit:
            cout << "  [STOP] Program Finished." << endl;
            return;
        }

        // show changes
        if (!jumped && instr.op != opPrint && instr.op != opInput && instr.op != opExit)
        {
            int newVal = memory[targetID];
            cout << "  [MEMORY] Updated '" << getArgName(targetID) << "'\n";
            cout << "           Value changed: " << oldVal << " -> " << newVal << endl;
        }

        cout << "\n  (Press ENTER to continue)";
        cin.get();

        if (!jumped)
            ip++;
    }
}