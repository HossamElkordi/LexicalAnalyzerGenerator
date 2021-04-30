//
// Created by hossam and a7ma yasser on 29/04/2021.
//

#include "Nfa.h"
//to create an nfa you have to take care of the following
//      *int start that indicates the start state almost everytime it is set to 1
//      *int end state it says the last state of the nfa
//      *int number of states it indicates the number of states in the nfa
//      *vector<int>accepting this is a vector that contains all the accepting states
//      *map<int,map<string,vector<int>>> this is the most important structure in the Nfa it
//  contains all the transition in the following manner indexing the map with the
//  the number of state returns a map that has as input a string that says what states
//  to go to if the nfa was at this state and received the string
//      *map<int,string>tags that has all the tags for the accepting states
static map<string,Nfa>temporaryMap;
Nfa::Nfa()  {
    start= 0;
    end=0;
    numberOfStates=0;
}
Nfa::Nfa(char oneLetter) {
    start= 1;
    end=2;
    accepting.push_back(2);
    string str="";
    str+=oneLetter;
    map<string,vector<int>>temp;
    vector<int>tempo;
    tempo.push_back(2);
    temp[str]=tempo;
    transitions[1]=temp;
    tags[2]=str;
}
Nfa Nfa::getThis() {
    Nfa temp=Nfa();
    temp.transitions=transitions;
    temp.end=end;
    temp.start=start;
    temp.numberOfStates=numberOfStates;
    temp.tags=tags;
    temp.accepting=accepting;
    return temp;
}


int Nfa::getStart() {
    return start;
}



int Nfa::getEnd() {
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
    if(a=='-'||a=='|'||a=='+'||a=='*'||a=='('||a==')'||'\\'){
        return true;
    }
    return false;
}

bool existsInTempMap(string target){
    map<string ,Nfa>::iterator it;
    for(it= temporaryMap.begin(); it != temporaryMap.end(); ++it){
        if(it->first==target)
            break;
    }
    if( it == temporaryMap.end())
        return false;
    return true;
}

void Nfa::createNfa(string reg,string name) {
//____________________stage one:preparation_______________________
//the next for loop creates an Nfa from each char that is not a separator or an operator
//in preparation for the next stage
    for(int i=0;i<reg.size();i++){
        string str;
        str+=reg[i];
        if((!isSep(reg[i]))||(i>0&&(isSep(reg[i])&&reg[i-1]=='\\'))){
            if(!existsInTempMap(str))
                temporaryMap[str]=Nfa(reg[i]);
        }
    }
//_________________end of stage one________________
//_________________stage two:looking for parenthesis___________
    for(int i=0;i<reg.size();i++){
        if((i>0&&reg[i]=='('&&reg[i-1]!='\\')||(i==0&&reg[i]=='(')){
            int end=0;
            while(reg[end+1+i]!=')'||reg[end+i]=='\\'){
                ++end;
            }
            Nfa newnfa=Nfa();
            newnfa.createNfa(reg.substr(i+1,end),NULL);
            temporaryMap[reg.substr(i,end+1)]=newnfa.getThis();
        }

    }

}

void Nfa::setend(int in) {
    end= in;
}

void Nfa::setstart(int in) {
    start= in;
}

vector<int> vectoroffsetter(vector<int> in, int amt){
    for(int i=0;i<in.size();++i){
        in[i]=in[i]+amt;
    }
    return in;
}

map<string,vector<int>>offestHelper(map<string,vector<int>>in,int amnt){
    map<string ,vector<int>> temp;
    for(map<string,vector<int>>::iterator it = in.begin(); it != in.end(); ++it) {
        temp[(it->first)]= vectoroffsetter(it->second,amnt);
    }
    return temp;
}


void Nfa::offset(int offsetAmnt) {
    map<int,map<string,vector<int>>> temp;
    for(map<int,map<string,vector<int>>>::iterator it = transitions.begin(); it != transitions.end(); ++it) {
        temp[(it->first)+offsetAmnt]=offestHelper(it->second,offsetAmnt);
    }
    transitions=temp;
    map<int,string>tempo;
    for(int i=0;i<accepting.size();++i){
        accepting[i]=accepting[i]+offsetAmnt;
    }
    for(map<int,string>::iterator it = tags.begin(); it != tags.end(); ++it) {
        tempo[it->first+offsetAmnt]=it->second;
    }

}
bool transitionMapContains(map<int,map<string,vector<int>>> in,int target){
    map<int,map<string,vector<int>>>::iterator it;
    for(it= in.begin(); it != in.end(); ++it){
        if(it->first==target)
            break;
    }
    if( it == in.end())
        return false;
    return true;
}

bool transitionMapContains(map<string,vector<int>> in,string target){
    map<string,vector<int>>::iterator it;
    for(it= in.begin(); it != in.end(); ++it){
        if(it->first==target)
            break;
    }
    if( it == in.end())
        return false;
    return true;
}

void Nfa::addEdge(int to, int from, string weight) {
    if(to>=start&&from>=start&&to<=end&&from<=end){
        if(transitionMapContains(transitions,from)){
            if(transitionMapContains(transitions[from],weight)){
                transitions[from][weight].push_back(to);
            }
            else{
                vector<int> tempo;
                tempo.push_back(to);
                transitions[from][weight]=tempo;
            }
        }
        else{
            map<string,vector<int>> tmp;
            vector<int>ttt;
            ttt.push_back(to);
            tmp[weight]=ttt;
            transitions[from]=tmp;
        }
    }
}








