//
// Created by hossam and a7ma yasser on 29/04/2021.
//

#include "Nfa.h"


Nfa::Nfa()  {
    start= State(false,NULL);
    end=start;
    states.push_back(start);
}
Nfa::Nfa(char oneLetter) {
    start= State(false,NULL);
    string str="";
    str+=oneLetter;
    State temp= State(true,str);
    states.push_back(start);
    states.push_back(temp);
    start.addTrans(temp,str);
    end=temp;
}

State Nfa::getStart() {
    return start;
}



State Nfa::getEnd() {
    return end;
}

void Nfa::andWith(Nfa second) {

}

void Nfa::orWith(Nfa second) {

}

void Nfa::kleen() {

}

void Nfa::pKleen() {

}

bool isSep(char a){
    if(a=='-'||a=='|'||a=='+'||a=='*'||a=='('||a==')'){
        return true;
    }
    return false;
}
string expanddashes(string in){
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

Nfa Nfa::createNfa(string reg,string name) {
    map<string,Nfa> temp;
    reg= expanddashes(reg);
    for(int i=0;i<reg.size();i++){
        if(!(reg[i]='\\'&& isSep(reg[i+1]))||!isSep(reg[i])){
            temp[reg[i]]=Nfa(reg[i]);
        }
    }

}

void Nfa::setend(State in) {
    end= in;
}

void Nfa::setstart(State in) {
    start= in;
}




