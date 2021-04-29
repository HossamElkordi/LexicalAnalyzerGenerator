//
// Created by hossam and a7ma yasser on 29/04/2021.
//

#ifndef LEXICALANALYZERGENERATOR_GLOBALSTRUCTURES_H
#define LEXICALANALYZERGENERATOR_GLOBALSTRUCTURES_H

#include "State.h"
#include <string>

struct transition{
    transition() {

    }

    State to;
    string weight;
};

#endif //LEXICALANALYZERGENERATOR_GLOBALSTRUCTURES_H
