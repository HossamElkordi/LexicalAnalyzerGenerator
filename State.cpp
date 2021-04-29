//
// Created by hossam on 29/04/2021.
//

#include "State.h"

State::State(bool accepting, string token_type) {
    isAccepting = accepting;
    type = token_type;
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

State::State() {
}

void State::addTrans(transition a) {
    edges.push_back(a);
}

void State::addTrans(State to, string weight) {
    transition temp;
    temp.to=to;
    temp.weight=weight;
}








