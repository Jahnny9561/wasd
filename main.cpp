#include <iostream>
#include <fstream>
#include <sstream>
#include "lexer.h"

using namespace std;

int main() {
    string filename;
    cout << "Enter the filename to read: ";
    cin >> filename;

    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: Could not open file " << filename << endl;
        return 1;
    }

    stringstream bufferStream;
    bufferStream << infile.rdbuf();
    string buffer = bufferStream.str();
    infile.close();

    tokenize(buffer);
    listall(symbolTable);

    return 0;
}
