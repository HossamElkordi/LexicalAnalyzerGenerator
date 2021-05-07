//
// Created by mina on 5/5/21.
//
#include "Token.h"
#include <fstream>
#include <set>
#include <map>
#include <vector>

using namespace std;

#ifndef LEXICALANALYZERGENERATOR_INPUTLANGUAGEPARSER_H
#define LEXICALANALYZERGENERATOR_INPUTLANGUAGEPARSER_H

class InputLanguageParser{
    private:
        map<set<int>, string> dfaAccepted;
        map<set<int>, map<string, set<int>>> graph;
        set<int> Start;

        vector<Token> search(const string& line);
    public:
        InputLanguageParser();
        InputLanguageParser(map<set<int>, map<string, set<int>>> dfaGraph, map<set<int>, string> dfaAcceptedStates, set<int> StartState);
        vector<Token> parseFile(const string &Path);

};
#endif //LEXICALANALYZERGENERATOR_INPUTLANGUAGEPARSER_H
