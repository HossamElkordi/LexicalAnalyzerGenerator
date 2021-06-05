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
    outPath = (argc > 4) ? argv[4] : "result.txt";

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

    InputLanguageParser ilp(inPath, dfaGraph, dfaAccepted, start);
//    vector<Token> toks = ilp.parseFile();

    Token t;
    while(true){
        t = ilp.getNextToken();
        if(t.GetLexeme() == "$" && t.GetType() == "eof") break;
    }

//    OutputGenerator op;
//    op.outputTable(dfaForm);
//    op.outputAccepting(accForm);
//    op.outputResult(outPath, toks);

    return 0;
}