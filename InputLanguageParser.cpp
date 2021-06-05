//
// Created by mina on 5/5/21.
//
#include <iostream>
#include "InputLanguageParser.h"

InputLanguageParser::InputLanguageParser() = default;

InputLanguageParser::InputLanguageParser(string path, map<set<int>, map<string, set<int>>> dfaGraph,
                                         map<set<int>, string> dfaAcceptedStates, set<int> StartState) {
    graph = dfaGraph;
    dfaAccepted = dfaAcceptedStates;
    Start = StartState;
    file.open(path, ios::in);
}

vector<Token> InputLanguageParser::search(const string &line) {
    vector<Token>answer;
    int old=0,i=0,temp = 0;
    string type,oldtype;
    set<int> CurrentState = Start;
    while(i<line.size())
    {
        if(graph[CurrentState].find(string(1,line.at(i))) != graph[CurrentState].end())
            CurrentState=graph[CurrentState][string(1,line.at(i))];
        else
        {
            if(type.empty() && oldtype.empty() && old != i)
                cout<<"Error found";
            else if(type.empty() && old != i)
            {
                backtrack:
                answer.emplace_back(oldtype,line.substr(old,temp-old+1));
                ++temp;
                i = temp;
                old = temp;
                CurrentState=Start;
                oldtype="";
                continue;
            }
            if(old != i)
                answer.emplace_back(type,line.substr(old,temp-old+1));
            if(string(1,line.at(i))==" " ||string(1,line.at(i))=="\t")
            {
                old = i+1;
                temp = i+1;
            }
            else
            {
                temp = i;
                old = i;
                --i;
            }
            CurrentState=Start;
            oldtype="";
        }
        if(dfaAccepted.find(CurrentState)!=dfaAccepted.end())
        {
            type=dfaAccepted[CurrentState];
            oldtype=type;
            temp = i;
        }
        else
            type = "";
        ++i;
    }
    type=dfaAccepted[CurrentState];
    if(type.empty())
        goto backtrack;
    answer.emplace_back(type,line.substr(old,temp-old+1));
    return answer;
}

vector<Token> InputLanguageParser::parseFile() {
    vector<Token> answer;
    string line;
    while(getline(file, line))
    {
        for(const Token& t:search(line))
            answer.emplace_back(t);
    }
    return answer;
}

Token InputLanguageParser::getNextToken() {
    if(file.eof()){
        return Token("eof", "$");
    }
    static vector<Token> tok;
    Token t;
    if(tok.empty()){
        string word;
        file >> word;
        tok = search(word);
    }
    t = tok.front();
    cout << t.GetLexeme() << endl;
    tok.erase(tok.begin());
    return t;
}
