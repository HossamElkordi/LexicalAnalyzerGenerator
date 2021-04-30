//
// Created by hossam on 30/04/2021.
//

#include "Dfa.h"

Dfa::Dfa() { }

Dfa::Dfa(map<int, map<string, vector<int>>> nfaGraph, list<char> inputs, map<int, string> acceStates) {
    nfa = nfaGraph;
    alphabet = inputs;
    acceStates = acceptingStates;
}

void Dfa::epsClosure(set<int> *from) {

}

void Dfa::move(set<int> *from, char input, set<int> *to) {

}

void Dfa::createDFA() {
    vector<set<int>> dStates;
    set<int> start;
    start.insert(1);
    dStates.push_back(start);

    while(!dStates.empty()){
        set<int> t = dStates.at(0);
        dStates.erase(dStates.begin());
        epsClosure(&t);
        for(char c : alphabet){
            set<int> u;
            move(&t, c, &u);
            epsClosure(&u);
            if(!contains(&dStates, u)){
                dStates.push_back(u);
            }
            graph[t][c] = u;
        }
        for(auto i = acceptingStates.begin(); i != acceptingStates.end(); ++i){
            if(t.find((*(i)).first) != t.end()){
                dfaAccepted[t] = (*(i)).second;
            }
        }
    }
}

bool Dfa::contains(vector<set<int>> *pVector, set<int> set) {
    for(auto i = pVector->begin(); i != pVector->end(); ++i){
        if((*i) == set) return true;
    }
    return false;
}
