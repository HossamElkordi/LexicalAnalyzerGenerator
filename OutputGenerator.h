//
// Created by hossam on 08/05/2021.
//
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "Token.h"

using namespace std;

#ifndef LEXICALANALYZERGENERATOR_OUTPUTGENERATOR_H
#define LEXICALANALYZERGENERATOR_OUTPUTGENERATOR_H

class OutputGenerator{
    public:
        OutputGenerator();
        void outputTable(map<string, map<string, string>> dfaForm);
        void outputAccepting(map<string, string> accForm);
        void outputResult(string filePath, vector<Token> tokens);
};

#endif //LEXICALANALYZERGENERATOR_OUTPUTGENERATOR_H
