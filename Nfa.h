//
// Created by hossam and a7ma yasser on 29/04/2021.
//

#ifndef LEXICALANALYZERGENERATOR_NFA_H
#define LEXICALANALYZERGENERATOR_NFA_H

#include <vector>
#include <map>
#include "GlobalStructures.h"

using namespace std;

class Nfa{

    private:

        list<State> states;
        void addEdge(State to, string weight);
        State start;
        State end;
    public:
        Nfa();
        Nfa(char oneLetter);
        void setstart(State in);
        void setend(State in );
        State getStart();
        State getEnd();
        Nfa createNfa(string reg,string name);
        void andWith(Nfa second);
        void orWith(Nfa second);
        void kleen();
        void pKleen();
};

#endif //LEXICALANALYZERGENERATOR_NFA_H
