#include <iostream>
#include <fstream>
#include <list>
#include <regex>


using namespace std;

void split(string str, string seperator, list<string> * strings);
void readFile();

int main() {
    readFile();
    return 0;
}

void readFile(){
    list<string> keywords;
    list<string> puncs;
    map<string, string> defs; //  not working
    map<string, string> regs; //  not working
    ifstream file;
    file.open("grammar.txt", ios::in);
    string line;
    while(getline(file, line)){
        if(regex_match(line, regex(R"([a-zA-Z]*[\s]*=[\s]*([a-zA-Z0-9]*|\||\s|\-|\+|\*|\(|\)|[\=]|[\>]|[\<]|[\!]|\\)*)"))){
            // definition
            line = regex_replace(line, regex("[\\s]"),"");
            list<string> def;
            split(line, "=", &def);
            defs[*(def.begin())] = *(++def.begin());
        }else if(regex_match(line, regex(R"([a-zA-Z]*[\s]*:[\s]*([a-zA-Z0-9]*|\||\s|\-|\+|\*|\(|\)|[\=]|[\>]|[\<]|[\!]|\\)*)"))){
            //regex
            line = regex_replace(line, regex("[\\s]"),"");
            list<string> reg;
            split(line, ":", &reg);
            regs[*(reg.begin())] = *(++reg.begin());
        }else if(regex_match(line, regex(R"({[\s]*[\w\s]*[\s]*})"))){
            //keywords
            line.erase(line.begin());
            line.erase(line.end());
            split(line, "[\\s]*", &keywords);
        }else if(regex_match(line, regex(R"([\[][\s]*[\W\s]*[\s]*[\]])"))){
            //puctuation
            line.erase(line.begin());
            line.erase(line.end());
            split(line, "[\\s]*", &puncs);
        }else{
            cout << "Undefined Rule" << endl;
        }
    }
}

void split(string str, string seperator, list<string> * strings){
    regex rgx(seperator);
    sregex_token_iterator iter(str.begin(),str.end(), rgx, -1);
    sregex_token_iterator end;
    for ( ; iter != end; ++iter) {
        if (*iter != "") {
            strings->push_back(*iter);
        }
    }
}