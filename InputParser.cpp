//
// Created by hossam on 30/04/2021.
//
#include <iostream>
#include <utility>
#include "InputParser.h"

InputParser::InputParser() = default;

InputParser::InputParser(string path) {
    filePath = path;
}

void InputParser::readFile() {
    fstream file;
    file.open(filePath, ios::in);
    string line;
    regex def(R"([a-zA-z]*[\s]*=[\s|a-zA-z0-9|\-|\+|\*|\(|\)|\|]*)");
    regex reg(R"([a-zA-z]*[\s]*:[\s|a-zA-z0-9|\-|\+|\*|\(|\)|\||\=|\<|>|\!\.|\/]*)");
    regex k(R"(\{[\s]*([a-z]*[\s]*)*\})");
    regex p(R"(\[[\s]*([\W]*[\s]*)*\])");
    int pri = 0;

    while(getline(file, line)){
        if(regex_match(line, def)){
            // definition
            parseDefsAndRegs(line, &definitions, false, pri);
        }else if(regex_match(line, reg)){
            //regex
            parseDefsAndRegs(line, &regexes, true, pri);
        }else if(regex_match(line, k)){
            //keywords
            parseKeysAndPuncs(line, &keywords, -1);
        }else if(regex_match(line, p)){
            //puctuation
            parseKeysAndPuncs(line, &punctuations, -1);
        }else{
            cout << line + ": Undefined Rule" << endl;
        }
        ++pri;
    }
}

void InputParser::parseKeysAndPuncs(string line, list<string> *storage, int priority) {
    line.erase(line.begin());
    line.erase(line.end() - 1);
    line = regex_replace(line, regex("\\\\"), "");
    split(line, "[\\s]+", storage);
    for(auto i : *storage){
        if(regexPriority.find(i) == regexPriority.end()){
            regexPriority[i] = priority;
        }
    }
}

void InputParser::parseDefsAndRegs(string line, map<string, string> *storage, bool isReg, int priority) {
    line = regex_replace(line, regex("[\\s]+"), "");
    list<string> id;
    split(line, (isReg) ? ":" : "=", &id);
    string type = *(id.begin());
    string reg = *(--id.end());
    replaceRanges(&reg);
    replacePreDefined(&reg);
    reg = regex_replace(reg, regex("\\\\L"), "$");
    if(isReg){
        storage->insert({type, reg});
        regexPriority[type] = priority;
    }else{
        storage->insert({type, "(" + reg + ")"});
    }
}

void InputParser::replaceRanges(string* reg) {
    regex r("[a-zA-z0-9]\\-[a-zA-z0-9]");
    smatch match;
    regex_search(*reg, match, r);
    while(match.size()  > 0){
        reg->replace(reg->find(match.str(0)), 3, expandDashes(match.str(0)));
        regex_search(*reg, match, r);
    }
}

void InputParser::replacePreDefined(string *reg) {
    size_t pos;
    for(auto i = definitions.rbegin(); i != definitions.rend(); ++i){
        pos = reg->find((*(i)).first);
        while(pos != string::npos){
            reg->replace(pos, (*(i)).first.size(), (*(i)).second);
            pos = reg->find((*(i)).first);
        }
    }
}

string InputParser::expandDashes(string in) {
    char x,y;
    vector<char> temp;string tempo="";
    for(int i=0;i<in.length();++i){
        tempo="";
        temp.clear();
        if(in[i]=='-'&&in[i-1]!='\\'&&in[i-1]<in[i+1]){
            x=in[i-1];
            y=in[i+1];
            while(x<=y)
                temp.push_back(x++);
            tempo+=temp[0];
            for(int j=1;j<temp.size();j++){
                tempo+='|';
                tempo+=temp[j];
            }
            in.replace(i-1,3,tempo);
        }
    }
    return in;
}

void InputParser::split(string str, string seperator, list<string> *strings) {
    regex rgx(seperator);
    sregex_token_iterator iter(str.begin(),str.end(), rgx, -1);
    sregex_token_iterator end;
    for ( ; iter != end; ++iter) {
        if (*iter != "") {
            strings->push_back(*iter);
        }
    }
}

list<string> InputParser::getKeywords() {
    return keywords;
}

list<string> InputParser::getPunctuations() {
    return punctuations;
}

map<string, string> InputParser::getRegexes() {
    return regexes;
}

map<string, string> InputParser::getDefinitions() {
    return definitions;
}

map<string, int> InputParser::getRegexPriority() {
    return regexPriority;
}