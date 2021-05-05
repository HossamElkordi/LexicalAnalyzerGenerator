//
// Created by mina on 5/5/21.
//

#include "Token.h"

using namespace std;

string Token::GetType() {
    return this->type;
}

string Token::GetLexeme() {
    return this->lexeme;
}

Token::Token(string type, string lexeme) {
    this->lexeme=lexeme;
    this->type=type;
}
