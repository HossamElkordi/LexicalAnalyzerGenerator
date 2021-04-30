//
// Created by hossam on 30/04/2021.
//
#include "State.h"
#include "GlobalStructures.h"
#include <map>
#include <vector>

using namespace std;

#ifndef LEXICALANALYZERGENERATOR_DFA_H
#define LEXICALANALYZERGENERATOR_DFA_H

class Dfa{
    private:
        list<char> alphabet;
        map<int, string> acceptingStates;
        map<set<int>, string> dfaAccepted;
        map<int, map<string, vector<int>>> nfa;
        map<set<int>, map<char, set<int>>> graph;
        set<int> start;

        bool contains(vector<set<int>> *pVector, set<int> set);

    public:
        Dfa();
        Dfa(map<int, map<string, vector<int>>> nfaGraph, list<char> inputs, map<int, string> acceStates);
        void epsClosure(set<int> *from);
        void move(set<int> *from, char input, set<int> *to);
        void createDFA();
};

#endif //LEXICALANALYZERGENERATOR_DFA_H
