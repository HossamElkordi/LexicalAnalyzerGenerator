//
// Created by hossam on 29/04/2021.
//

#include "State.h"

State::State() { }

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









