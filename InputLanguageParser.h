//
// Created by mina on 5/5/21.
//
#include "Dfa.h"
#include "Token.h"

using namespace std;

#ifndef LEXICALANALYZERGENERATOR_INPUTLANGUAGEPARSER_H
#define LEXICALANALYZERGENERATOR_INPUTLANGUAGEPARSER_H

vector<Token>parseFile(const string& Path,Dfa minimizedDFA);
#endif //LEXICALANALYZERGENERATOR_INPUTLANGUAGEPARSER_H
