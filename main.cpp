#include <iostream>
#include <fstream>
#include <sstream>
#include "lexer.h"
#include "parser.h"
#include "semantic.h"
#include "interpreter.h"
using namespace std;

int main(int argc, char *argv[])
{
    string filename;

    if (argc > 1)
    {
        filename = argv[1];
    }
    else
    {
        cout << "Enter the filename to read: ";
        cin >> filename;
    }
    ifstream infile(filename);
    if (!infile)
    {
        cerr << "Error: Could not open file " << filename << endl;
        return 1;
    }

    stringstream bufferStream;
    bufferStream << infile.rdbuf();
    string buffer = bufferStream.str();
    infile.close();

    // Tokenize
    tokenize(buffer);

    // Start parser
    bool parseSuccess = parser();

    // Check if parser is successful
    if (!parseSuccess)
    {
        cout << "Program stopped" << endl;
        return 1;
    }

    listall(symbolTable);
    listStream(tokenStream);
    printIR();

    cout << "Run normally (r) or debug (d)? ";
    char mode;
    cin >> mode;

    if (mode == 'd')
    {
        debugProgram();
    }
    else
    {
        runProgram();
    }

    cout << "\nPress Enter to exit...";

    cin.ignore();
    cin.get();

    return 0;
}
