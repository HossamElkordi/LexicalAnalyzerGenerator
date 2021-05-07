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
        string filePath;
        list<string> keywords;
        list<string> punctuations;
        map<string, string> regexes;
        map<string, int> regexPriority;
        map<string, string> definitions;

        void split(string str, string seperator, list<string> * strings);
        void parseKeysAndPuncs(string line, list<string> *storage, int priority);
        void parseDefsAndRegs(string line, map<string, string> *storage, bool isReg, int priority);
        void replaceRanges(string* reg);
        void replacePreDefined(string* reg);
        string expandDashes(string in);
    public:
        InputParser();
        explicit InputParser(string path);
        void readFile();
        list<string> getKeywords();
        list<string> getPunctuations();
        map<string, string> getRegexes();
        map<string, string> getDefinitions();
        map<string, int> getRegexPriority();
};

#endif //LEXICALANALYZERGENERATOR_INPUTPARSER_H
