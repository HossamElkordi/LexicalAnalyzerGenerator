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

    public:
        Nfa();
        Nfa(char oneLetter);
        int start;
        int end;
        vector<int>accepting;
        map<int,string> tags;
        map<int,map<string,vector<int>>> transitions;
        int numberOfStates;
        void addEdge(int to,int from, string weight);
        void setstart(int in);
        void offset(int offsetAmnt);
        void setend(int in );
        void createNfa(string reg,string name);
        void andWith(Nfa second);
        void orWith(Nfa second);
        void kleen();
        void pKleen();
        int getStart();
        int getEnd();
        Nfa getThis();

};

#endif //LEXICALANALYZERGENERATOR_NFA_H
