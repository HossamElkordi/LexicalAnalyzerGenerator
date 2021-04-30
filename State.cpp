//
// Created by hossam on 29/04/2021.
//

#include "State.h"

State::State() { }

State::State(int sub) {
    subsetState.push_back(sub);
}

bool State::getIsAcc() {
    return isAccepting;
}

string State::getType() {
    return type;
}

void State::setType(string token_type) {
    type = token_type;
}

void State::setAcc(bool acc) {
    isAccepting = acc;
}

void State::addSub(int sub) {
    subsetState.push_back(sub);
}

void State::addTrans(char input, int to) {
    if(trans.find(input) == trans.end()){
        set<int> s;
        s.insert(to);
        trans[input] = s;
    }else{
        (trans[input]).insert(to);
    }
}









