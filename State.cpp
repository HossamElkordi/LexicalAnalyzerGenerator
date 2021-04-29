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

list <transition> State::getEdges() {
    return edges;
}

void State::addEdge(State to, string weight) {
    transition edge;
    edge.to = to;
    edge.weight = weight;
    edges.push_back(edge);
}




