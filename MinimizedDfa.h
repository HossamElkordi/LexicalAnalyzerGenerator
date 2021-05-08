//
// Created by hossam on 07/05/2021.
//

#include <map>
#include <set>
#include <vector>
#include <string>

using namespace std;

#ifndef LEXICALANALYZERGENERATOR_MINIMIZEDDFA_H
#define LEXICALANALYZERGENERATOR_MINIMIZEDDFA_H

void minimizeDfa(map<set<int>, map<string, set<int>>>* graph, map<set<int>, string>* dfaAccepted, set<string> alphabet, set<int>* start);

#endif //LEXICALANALYZERGENERATOR_MINIMIZEDDFA_H
