#include <iostream>
#include "InputParser.h"
#include "Dfa.h"
#include "Nfa.h"
#include "MinimizedDfa.h"
#include "InputParser.h"
#include "Token.h"
#include <set>

using namespace std;

//void printSet(set<int> s){
//    cout << "(";
//    for(int i : s){
//        cout << i;
//        cout << ",";
//    }
//    cout << ")";
//}
//
//int main() {
//
//////  test the dfa
////    map<int, map<string, vector<int>>> nfa;
////    list<string> alpha = {"0", "1"};
////    map<int, string> acc;
////    map<string, int> pri;
////    pri["done"] = 1;
////    acc[2] = "done";
////    acc[4] = "done";
////    nfa[1]["0"] = {2, 4};
////    nfa[2]["1"] = {1, 4};
////    nfa[3]["0"] = {2};
////    nfa[3]["1"] = {3};
////    nfa[4]["0"] = {3};
////    nfa[4]["1"] = {3};
////    Dfa dfa(nfa, alpha, acc, pri);
////    dfa.createDFA();
////    map<set<int>, map<string, set<int>>> dfaGraph = dfa.getGraph();
////    map<set<int>, string> dfaAcc = dfa.getDfaAccepted();
////
////    cout << "DFA State Count: ";
////    cout << dfaGraph.size() << endl;
////
////    for(auto i : dfaGraph){
////        printSet(i.first);
////        cout << "\t\t0 - > ";
////        printSet(i.second["0"]);
////        cout << "\t\t1 - > ";
////        printSet(i.second["1"]);
////        cout << "\n";
////    }
////    cout << "\n";
////    for(auto i : dfaAcc){
////        printSet(i.first);
////        cout << " as " + i.second << endl;
////    }
////    InputParser parser;
////    parser.readFile();
//////  test the parser
////    map<string, string> defs = parser.getDefinitions();
////    cout << "Regular Definitions: " << endl;
////    for(auto i : defs){
////        cout << "\t" + i.first + ": " + i.second << endl;
////    }
////    map<string, string> regs = parser.getRegexes();
////    cout << "\nRegular Expressions: " << endl;
////    for(auto i : regs){
////        cout << "\t" + i.first + ": " + i.second << endl;
////    }
////    list<string> keys = parser.getKeywords();
////    cout << "Keywords: ";
////    for(auto i = keys.begin(); i != keys.end(); ++i){
////        cout << *i + " ";
////    }
////    list<string> puncs = parser.getPunctuations();
////    cout << "\nPunctuations: ";
////    for(auto i = puncs.begin(); i != puncs.end(); ++i){
////        cout << *i + " ";
////    }
//
//    // Nfa.create takes a single regex and outputs it Nfa
//    //the is a function called orWith that x1.orWith(x2) groups x1 and 2 together
//    //nfa's testing unit
//
//
//
//    //end
//
////    Main Program
//    InputParser ip;
//    ip.readFile();
//    Nfa nfa;
//    map<string, string> regs = ip.getRegexes();
////    regs["num"]="(a)((a)|(0))*";
////    regs["relop"]="\\=\\=|!\\=";
//    Nfa temp=Nfa();
//    temp=temp.getfromlist(regs);
//    //temp.createNfa("(a|b)","7amo");
//    //printing transitions
////    for(map<int,map<string,vector<int>>>::iterator it = temp.transitions.begin(); it != temp.transitions.end(); ++it) {
////        cout<<it->first<<"--> ";
////        for(map<string,vector<int>>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
////            cout<<"   "<<it2->first;
////            for (int j = 0; j < it2->second.size(); ++j) {
////                cout<<"-"<<it2->second[j]<<"  ";
////            }
////            cout<<endl;
////        }
////        cout<<endl;
////    }
//    //printing accepted states
////    for (int i = 0; i < temp.accepting.size(); ++i) {
////        cout<<"accepted state"<<i<<" "<<temp.accepting[i]<<endl;
////    }
////    //printing tags
////    for(map<int,string>::iterator it2 = temp.tags.begin(); it2 != temp.tags.end(); ++it2) {
////        cout<<it2->first<<" : "<<it2->second<<endl;
////    }
//    Dfa dfa(temp.transitions, temp.getAlphabets(), temp.tags, ip.getRegexPriority());
//    dfa.createDFA();
//    map<set<int>, map<string, set<int>>> dfaGraph = dfa.getGraph();
//    map<set<int>, string> dfaAcc = dfa.getDfaAccepted();
//    string start;
//    map<string, map<string, string>> tranlatedGraph;
//    map<string, string> translatedAcc;
//    dfa.translateGraph(&tranlatedGraph, &translatedAcc, &start);
//
//    cout << "DFA State Count: ";
//    cout << translatedAcc.size() << endl;
//
//   /* for(auto i : dfaGraph){
//        printSet(i.first);
//        cout << "\t\t0 - > ";
//        printSet(i.second["0"]);
//        cout << "\t\t1 - > ";
//        printSet(i.second["1"]);
//        cout << "\n";
//    }*/
//    cout << "\n";
//    for(auto i : translatedAcc){
////        printSet(i.first);
//        cout << i.first + "\tas\t\t" + i.second << endl;
//    }
//
////    End Of Main Program
//
//    return 0;
//}

int main(int argc, char** argv){
    string gramPath, inPath;
    list<string> temp;
    gramPath = (argc > 2) ? argv[2] : "grammar.txt";
    inPath = (argc > 2) ? argv[3] : "input.txt";

    InputParser ip(gramPath);
    ip.readFile();
    map<string, string> regs = ip.getRegexes();
    for(auto i : ip.getKeywords()){
        regs[i] = i;
    }
    for(auto i : ip.getPunctuations()){
        regs[i] = i;
    }

    Nfa nfa = Nfa();
    nfa = nfa.getfromlist(regs);

    Dfa dfa(nfa.transitions, nfa.getAlphabets(), nfa.tags, ip.getRegexPriority());
    dfa.createDFA();
    map<set<int>, map<string, set<int>>> dfaGraph = dfa.getGraph();
    map<set<int>, string> dfaAccepted = dfa.getDfaAccepted();
    set<int> start = dfa.getStart();

    minimizeDfa(&dfaGraph, &dfaAccepted, nfa.getAlphabets(), &start);

//    e3mel el parametersmen el variables ely hena badal Dfa
//    vector<Token> output = parseFile(inPath,Dfa minimizedDFA);

    return 0;
}