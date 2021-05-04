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
        set<string> alphabet;
        map<int, string> acceptingStates;
        map<int, map<string, vector<int>>> nfa;
        map<string, int> regexPriority;
        map<set<int>, string> dfaAccepted;
        map<set<int>, map<string, set<int>>> graph;
        set<int> start;

        bool contains(vector<set<int>> *pVector, set<int> set);
        bool isSubset(set<int>* from, set<int>* to);

    public:
        Dfa();
        Dfa(map<int, map<string, vector<int>>> nfaGraph, set<string> inputs, map<int, string> acceStates, map<string, int> regPri);
        void epsClosure(set<int> *from);
        void move(set<int> *from, string input, set<int> *to);
        void createDFA();
        map<set<int>, map<string, set<int>>> getGraph();
        map<set<int>, string> getDfaAccepted();
        set<int> getStart();
};

#endif //LEXICALANALYZERGENERATOR_DFA_H
