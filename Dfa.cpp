//
// Created by hossam on 30/04/2021.
//

#include "Dfa.h"

Dfa::Dfa() = default;

Dfa::Dfa(map<int, map<string, vector<int>>> nfaGraph, list<string> inputs, map<int, string> acceStates, map<string, int> regPri) {
    nfa = nfaGraph;
    alphabet = inputs;
    acceptingStates = acceStates;
    regexPriority = regPri;
}

void Dfa::epsClosure(set<int> *from) {
    if(from->empty()) return;
    vector<int> trans;
    set<int> to, temp;
    move(from, "$", &to);
    while(!to.empty()){
        copy(to.begin(), to.end(), inserter(temp, temp.begin()));
        to.clear();
        move(&temp, "$", &to);
        copy(temp.begin(), temp.end(), inserter(*from, from->begin()));
        temp.clear();
    }
}

void Dfa::move(set<int> *from, string input, set<int> *to) {
    if(from->empty()) return;
    vector<int> trans;
    for(int i : *from){
        trans = nfa[i][input];
        copy(trans.begin(), trans.end(), inserter(*to, to->begin()));
    }
}

void Dfa::createDFA() {
    vector<set<int>> dStates, checker;
    set<int> start;
    start.insert(1);
    dStates.push_back(start);
    bool isStart = true;

    while(!dStates.empty()){
        set<int> t = dStates.at(0), u;
        dStates.erase(dStates.begin());
        checker.push_back(t);
        epsClosure(&t);
        if(isStart){
            start = t;
            isStart = false;
        }
        for(string c : alphabet){
            move(&t, c, &u);
            epsClosure(&u);
            if(!contains(&dStates, u) && !contains(&checker, u)){
                if(!u.empty()) dStates.push_back(u);
            }
            graph[t][c] = u;
            u.clear();
        }
        for(auto & acceptingState : acceptingStates){
            if(t.find(acceptingState.first) != t.end()){
                if(dfaAccepted.find(t) != dfaAccepted.end()){
                    if(dfaAccepted[t] > acceptingState.second) dfaAccepted[t] = acceptingState.second;
                }else{
                    dfaAccepted[t] = acceptingState.second;
                }
            }
        }
    }
}

bool Dfa::contains(vector<set<int>> *pVector, set<int> set) {
    for(auto & i : *pVector){
        if(i == set) return true;
    }
    return false;
}

map<set<int>, map<string, set<int>>> Dfa::getGraph() {
    return graph;
}

map<set<int>, string> Dfa::getDfaAccepted() {
    return dfaAccepted;
}

set<int> Dfa::getStart() {
    return start;
}