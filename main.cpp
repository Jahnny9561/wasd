#include <iostream>
#include <fstream>
#include <sstream>
#include "lexer.h"
#include "parser.h"
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

    //Tokenize
    tokenize(buffer);

    //Start parser
    bool parseSuccess = parser();

    //Check if parser is successful
    if(!parseSuccess) {
        cout<<"Program stopped"<<endl;
        return 1;
    }

    listall(symbolTable);
    listStream(tokenStream);
    
    return 0;
}
