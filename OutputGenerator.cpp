//
// Created by hossam on 08/05/2021.
//

#include "OutputGenerator.h"

OutputGenerator::OutputGenerator() = default;

void OutputGenerator::outputTable(map<string, map<string, string>> dfaForm) {
    ofstream file("Transition Table.txt");
    int s = 0;
    auto i = dfaForm.find("S" + to_string(s));
    while(i != dfaForm.end()){
        file << i->first + "\t";
        for(auto j : i->second){
            file << j.first + ":" + ((j.second.empty()) ? "__" : j.second) + "\t";
        }
        file << "\n";
        i = dfaForm.find("S" + to_string(++s));
    }
    file.close();
}

void OutputGenerator::outputAccepting(map<string, string> accForm) {
    ofstream file("Accepting States.txt");
    for(auto i : accForm){
        file << i.first + ":\t" + i.second + "\n";
    }
    file.close();
}

void OutputGenerator::outputResult(string filePath, vector<Token> tokens) {
    ofstream file(filePath);
    for(auto i : tokens){
        file << i.GetType() + "\t\t" + i.GetLexeme() + "\n";
    }
    file.close();
}
