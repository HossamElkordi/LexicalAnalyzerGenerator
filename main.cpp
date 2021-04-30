#include <iostream>
#include "InputParser.h"
#include <set>

using namespace std;

int main() {
    InputParser parser;
    parser.readFile();
//  test the parser
    map<string, string> defs = parser.getDefinitions();
    cout << "Regular Definitions: " << endl;
    for(auto i : defs){
        cout << "\t" + i.first + ": " + i.second << endl;
    }
    map<string, string> regs = parser.getRegexes();
    cout << "\nRegular Expressions: " << endl;
    for(auto i : regs){
        cout << "\t" + i.first + ": " + i.second << endl;
    }
    list<string> keys = parser.getKeywords();
    cout << "Keywords: ";
    for(auto i = keys.begin(); i != keys.end(); ++i){
        cout << *i + " ";
    }
    list<string> puncs = parser.getPunctuations();
    cout << "\nPunctuations: ";
    for(auto i = puncs.begin(); i != puncs.end(); ++i){
        cout << *i + " ";
    }
    return 0;
}