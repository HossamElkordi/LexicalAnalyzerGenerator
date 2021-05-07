//
// Created by mina on 5/5/21.
//
#include <string>

using namespace std;

#ifndef LEXICALANALYZERGENERATOR_TOKEN_H
#define LEXICALANALYZERGENERATOR_TOKEN_H
class Token{
    private:
        string type;
        string lexeme;
    public:
        Token();
        Token(string type,string lexeme);
        string GetType();
        string GetLexeme();
};
#endif //LEXICALANALYZERGENERATOR_TOKEN_H
