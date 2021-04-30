//
// Created by hossam on 30/04/2021.
//

#ifndef LEXICALANALYZERGENERATOR_INPUTPARSER_H
#define LEXICALANALYZERGENERATOR_INPUTPARSER_H

#include <fstream>
#include <list>
#include <regex>

using namespace std;

class InputParser{
    private:
        list<string> keywords;
        list<string> punctuations;
        map<string, string> regexes;
        map<string, string> definitions;
        const string filePath = "grammar.txt";

        void split(string str, string seperator, list<string> * strings);
        void parseKeysAndPuncs(string line, list<string> *storage);
        void parseDefsAndRegs(string line, map<string, string> *storage, bool isReg);
        void replaceRanges(string* reg);
        void replacePreDefined(string* reg);
        string expandDashes(string in);
    public:
        InputParser();
        void readFile();
        list<string> getKeywords();
        list<string> getPunctuations();
        map<string, string> getRegexes();
        map<string, string> getDefinitions();
};

#endif //LEXICALANALYZERGENERATOR_INPUTPARSER_H
