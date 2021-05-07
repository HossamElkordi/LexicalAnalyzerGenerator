//
// Created by hossam and a7ma yasser on 29/04/2021.
//

#ifndef LEXICALANALYZERGENERATOR_NFA_H
#define LEXICALANALYZERGENERATOR_NFA_H

#include <vector>
#include <map>
#include <set>

using namespace std;

class Nfa{

    public:
        Nfa();
        Nfa(char oneLetter);
        int start;
        int end;
        vector<int>accepting;
        map<int,string> tags;
        map<int,map<string,vector<int>>> transitions;
        int numberOfStates;
        void addEdge(int to,int from, string weight);
        void setstart(int in);
        void offset(int offsetAmnt);
        void setend(int in );
        void createNfa(string reg,string type);
        void andWith(Nfa second);
        void orWith(Nfa second);
        void kleen();
        void pKleen();
        void executeString(string reg);
        int getStart();
        int getEnd();
        string parenthesis(string reg);
        Nfa getThis();
        void thiseuqalsnfa(Nfa temp);
        Nfa orAll(vector<Nfa> in);
        set<string> getAlphabets();
        Nfa getfromlist(map<string,string> in);
};

#endif //LEXICALANALYZERGENERATOR_NFA_H
