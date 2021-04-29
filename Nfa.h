//
// Created by hossam on 29/04/2021.
//

#ifndef LEXICALANALYZERGENERATOR_NFA_H
#define LEXICALANALYZERGENERATOR_NFA_H

#include <vector>
#include <map>
#include "GlobalStructures.h"

using namespace std;

class Nfa{

    private:
        State start;
    public:
        Nfa();
        State getStart();
        void createNfa(string reg);
};

#endif //LEXICALANALYZERGENERATOR_NFA_H
