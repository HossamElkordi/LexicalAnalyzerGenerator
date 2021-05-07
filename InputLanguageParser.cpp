//
// Created by mina on 5/5/21.
//
#include "InputLanguageParser.h"

InputLanguageParser::InputLanguageParser() = default;

InputLanguageParser::InputLanguageParser(map<set<int>, map<string, set<int>>> dfaGraph,
                                         map<set<int>, string> dfaAcceptedStates, set<int> StartState) {
    graph = dfaGraph;
    dfaAccepted = dfaAcceptedStates;
    Start = StartState;
}

vector<Token> InputLanguageParser::search(const string &line) {
    vector<Token>answer;
    int old=0,temp = 0,i=0;
    string type;
    //TODO start state initialize
    set<int> CurrentState = Start;
    while(i<line.size())
    {
        if(graph[CurrentState].find(to_string(line.at(i))) != graph[CurrentState].end())
            CurrentState=graph[CurrentState][to_string(line.at(i))];
        else
        {
            answer.emplace_back(type,line.substr(old,temp+1));
            temp = i;
            old = i;
            --i;
            CurrentState=Start;
        }
        if(dfaAccepted.find(CurrentState)!=dfaAccepted.end())
        {
            type=dfaAccepted[CurrentState];
            temp = i;
        }
        ++i;
    }
    if(i == temp + 1)
    {
        type=dfaAccepted[CurrentState];
        answer.emplace_back(type,line.substr(old,i));
    }
    return answer;
}

vector<Token> InputLanguageParser::parseFile(const string &Path) {
    vector<Token> answer;
    fstream file;
    file.open(Path, ios::in);
    string line;
    while(getline(file, line))
    {
        for(const Token& t:search(line))
            answer.emplace_back(t);
    }
    return answer;
}