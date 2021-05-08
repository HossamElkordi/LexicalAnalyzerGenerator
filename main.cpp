#include <iostream>
#include "InputParser.h"
#include "InputLanguageParser.h"
#include "Dfa.h"
#include "Nfa.h"
#include "MinimizedDfa.h"
#include "Token.h"
#include "OutputGenerator.h"

using namespace std;

void printSet(set<int> s){
    cout << "(";
    for(int i : s){
        cout << i;
        cout << " ";
    }
    cout << ")";
}

int main(int argc, char** argv){
    string gramPath, inPath, outPath;
    list<string> temp;
    gramPath = (argc > 2) ? argv[2] : "grammar.txt";
    inPath = (argc > 3) ? argv[3] : "input.txt";
    inPath = (argc > 4) ? argv[4] : "result.txt";

    InputParser ip(gramPath);
    ip.readFile();
    map<string, string> regs = ip.getRegexes();
    for(auto i : ip.getKeywords()){
        regs[i] = i;
    }
    for(auto i : ip.getPunctuations()){
        regs[i] = "\\"+i;
    }

    Nfa nfa = Nfa();
    nfa = nfa.getfromlist(regs);
//_____________________
//    for(map<int,map<string,vector<int>>>::iterator it = nfa.transitions.begin(); it != nfa.transitions.end(); ++it) {
//        cout<<it->first<<"--> ";
//        for(map<string,vector<int>>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
//            cout<<"   "<<it2->first;
//            for (int j = 0; j < it2->second.size(); ++j) {
//                cout<<"-"<<it2->second[j]<<"  ";
//            }
//            cout<<endl;
//        }
//        cout<<endl;
//    }
//    for (int i = 0; i < nfa.accepting.size(); ++i) {
//        cout<<"acc "<<nfa.accepting[i]<<endl;
//    }
//    for(map<int,string>::iterator it2 = nfa.tags.begin(); it2 != nfa.tags.end(); ++it2) {
//        cout<<it2->first<<" "<<it2->second<<endl;
//    }
//    cout<<nfa.end<<endl<<endl;
    //_____________________________



    Dfa dfa(nfa.transitions, nfa.getAlphabets(), nfa.tags, ip.getRegexPriority());
    dfa.createDFA();
    map<set<int>, map<string, set<int>>> dfaGraph = dfa.getGraph();
    map<set<int>, string> dfaAccepted = dfa.getDfaAccepted();
    set<int> start = dfa.getStart();


    minimizeDfa(&dfaGraph, &dfaAccepted, nfa.getAlphabets(), &start);
    map<string, map<string, string>> dfaForm;
    map<string, string> accForm;
    string startState;
    dfa.translateGraph(&dfaForm, &accForm, &startState);

    InputLanguageParser ilp(dfaGraph, dfaAccepted, start);
    vector<Token> toks = ilp.parseFile(inPath);
    cout<<toks.empty();

    OutputGenerator op;
    op.outputTable(dfaForm);
    op.outputAccepting(accForm);
    op.outputResult(outPath, toks);

    return 0;
}