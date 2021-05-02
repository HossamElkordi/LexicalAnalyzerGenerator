#include <iostream>
#include "InputParser.h"
#include "Dfa.h"
#include "Nfa.h"
#include <set>

using namespace std;

void printSet(set<int> s){
    cout << "(";
    for(int i : s){
        cout << i;
        cout << ",";
    }
    cout << ")";
}

int main() {
////  test the dfa
//    map<int, map<string, vector<int>>> nfa;
//    list<string> alpha = {"0", "1"};
//    map<int, string> acc;
//    map<string, int> pri;
//    pri["done"] = 1;
//    acc[2] = "done";
//    acc[4] = "done";
//    nfa[1]["0"] = {2, 4};
//    nfa[2]["1"] = {1, 4};
//    nfa[3]["0"] = {2};
//    nfa[3]["1"] = {3};
//    nfa[4]["0"] = {3};
//    nfa[4]["1"] = {3};
//    Dfa dfa(nfa, alpha, acc, pri);
//    dfa.createDFA();
//    map<set<int>, map<string, set<int>>> dfaGraph = dfa.getGraph();
//    map<set<int>, string> dfaAcc = dfa.getDfaAccepted();
//
//    cout << "DFA State Count: ";
//    cout << dfaGraph.size() << endl;
//
//    for(auto i : dfaGraph){
//        printSet(i.first);
//        cout << "\t\t0 - > ";
//        printSet(i.second["0"]);
//        cout << "\t\t1 - > ";
//        printSet(i.second["1"]);
//        cout << "\n";
//    }
//    cout << "\n";
//    for(auto i : dfaAcc){
//        printSet(i.first);
//        cout << " as " + i.second << endl;
//    }
//    InputParser parser;
//    parser.readFile();
////  test the parser
//    map<string, string> defs = parser.getDefinitions();
//    cout << "Regular Definitions: " << endl;
//    for(auto i : defs){
//        cout << "\t" + i.first + ": " + i.second << endl;
//    }
//    map<string, string> regs = parser.getRegexes();
//    cout << "\nRegular Expressions: " << endl;
//    for(auto i : regs){
//        cout << "\t" + i.first + ": " + i.second << endl;
//    }
//    list<string> keys = parser.getKeywords();
//    cout << "Keywords: ";
//    for(auto i = keys.begin(); i != keys.end(); ++i){
//        cout << *i + " ";
//    }
//    list<string> puncs = parser.getPunctuations();
//    cout << "\nPunctuations: ";
//    for(auto i = puncs.begin(); i != puncs.end(); ++i){
//        cout << *i + " ";
//    }
    Nfa temp=Nfa();
    temp.createNfa("a|b","a", true);
    return 0;
}