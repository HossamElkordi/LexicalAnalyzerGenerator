//
// Created by hossam and a7ma yasser on 29/04/2021.
//

#include <iostream>
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
Nfa::Nfa()  =  default;
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
    numberOfStates=2;
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

void Nfa::thiseuqalsnfa(Nfa temp){
    transitions=temp.transitions;
    end=temp.end;
    start=temp.start;
    numberOfStates=temp.numberOfStates;
    tags=temp.tags;
    accepting=temp.accepting;
}

int Nfa::getStart() {
    return start;
}

int getNext(string reg, int start){
    if(reg[start]!='('){
        if(reg[start]=='\\'){
            return start+1;
        }
        return start;
    }
    int count=-1;
    while(start<reg.size()){
        if(reg[start]=='(')
            ++count;
        if(reg[start]==')'&&reg[start-1]!='\\'){
            if(count==0)
                return start;
            --count;

        }
        ++start;
    }
    return -1;
}

int Nfa::getEnd() {
    return end;
}

void Nfa::andWith(Nfa second) {
    if(numberOfStates==1){
        transitions=second.transitions;
        tags=second.tags;
        start=second.start;
        end=second.end;
        accepting=second.accepting;
        numberOfStates=second.numberOfStates;
        return;
    }
    string tg=tags[end];
    second.offset(numberOfStates);
    for (int i = 0; i < accepting.size(); ++i) {
        addEdge(second.start,accepting[i],"$");
    }
    numberOfStates+=second.numberOfStates;
    accepting=second.accepting;
    tags=second.tags;
    end=second.end;
    for(map<int,map<string,vector<int>>>::iterator it = second.transitions.begin(); it != second.transitions.end(); ++it) {
        transitions[it->first]=it->second;
    }
    for(map<int,string>::iterator it2 = tags.begin(); it2 != tags.end(); ++it2) {
        tags[it2->first]=tg+it2->second;
    }
}

void Nfa::orWith(Nfa second) {
    offset(1);
    numberOfStates++;
    second.offset(numberOfStates);
    addEdge(start,1,"$");
    addEdge(second.start,1,"$");
    numberOfStates+=second.numberOfStates;
    numberOfStates++;
    for(map<int,map<string,vector<int>>>::iterator it = second.transitions.begin(); it != second.transitions.end(); ++it) {
        transitions[it->first]=it->second;
    }
    for(int i=0;i<second.accepting.size();++i){
        accepting.push_back(second.accepting[i]);

    }
    for(map<int,string>::iterator it = second.tags.begin(); it != second.tags.end(); ++it) {
        tags[it->first]=it->second;
    }
    for (int i = 0; i < accepting.size();++i){
        addEdge(numberOfStates,accepting[i],"$");

    }
    accepting.push_back(numberOfStates);
    end=numberOfStates;
    start=1;
    string tg;
    bool flag=false;
    for(map<int,string>::iterator it2 = tags.begin(); it2 != tags.end(); ++it2) {
        if(flag)
            tg+="|";
        else
            flag= true;
        tg+=it2->second;

    }
    tags[end]=tg;
}

void Nfa::kleen() {
    string tg="("+tags[end]+")";
    tg+="*";
    numberOfStates++;
    start=1;
    addEdge(numberOfStates,1,"$");
    for (int i = 0; i < accepting.size();++i){
        addEdge(numberOfStates,accepting[i],"$");
    }
    accepting.push_back(numberOfStates);
    end=numberOfStates;
    addEdge(start,end,"$");
    for (int i = 0; i <accepting.size(); ++i) {
        tags[accepting[i]]=tg;
    }
}

void Nfa::pKleen() {
    string tg="("+tags[end]+")";
    tg+="+";
    numberOfStates++;
    start=1;
    for (int i = 0; i < accepting.size();++i){
        addEdge(numberOfStates,accepting[i],"$");
    }
    accepting.push_back(numberOfStates);
    end=numberOfStates;
    addEdge(start,end,"$");
    for (int i = 0; i <accepting.size(); ++i) {
        tags[accepting[i]]=tg;
    }
}



string Nfa::parenthesis(string reg) {
    //_________________stage two parenthesising for the kleen closure_________
    for(int i=1;i<reg.size();i++){
        if((reg[i]=='*'||reg[i]=='+')&&reg[i-1]!='\\'){
            if(i==1){
                reg.insert(i,")");
                i++;
                reg.insert(i-2,"(");
                i++;
            }
            else if (reg[i-1]==')'&&reg[i-2]!='\\'){
                /*int j=i-2;
                int count=0;
                while(j>=0){
                    if(reg[j]!='('){
                        if(reg[j]==')'){++count;}
                        --j;
                    }
                    else if(j!=0){
                        if(count==0){
                            reg.insert(j,"(");
                            i++;
                            break;
                        }
                        else{
                            --count;
                            --j;
                        }

                    }
                    else{
                        reg.insert(j,"(");
                        ++i;
                        break;
                    }
                }
                reg.insert(i+1,")");*/
                continue;

            }
            else{
                reg.insert(i+1,")");
                reg.insert(i,")");
                i++;
                reg.insert(i-2,"((");
                i+=2;
            }
        }
    }
    return reg;
}

bool containsor(string reg){
    for (int i = 0; i < reg.size(); ++i) {
        if(reg[i]=='|'&&reg[i-1]!='\\'){
            return true;
        }
    }
    return false;
}

void Nfa::executeString(string reg){
    int i=0;
    Nfa prev;
    prev.start=0;
    start=0;
    while(i<reg.size()){
        if(reg[i]!='\\'&&reg[i]!='('&&reg[i]!='*'&&reg[i]!='+'){
            if(start==0&&prev.start!=0){
                thiseuqalsnfa(prev);
            }
            else if(start!=0&&prev.start!=0){
                andWith(prev);
            }
            prev=Nfa(reg[i]);
            ++i;
        }
        else if((i==0&&reg[i]=='(')||(reg[i]=='('&&reg[i-1]!='\\')){
            if(start==0&&prev.start!=0){
                thiseuqalsnfa(prev);
            }
            else if(start!=0&&prev.start!=0){
                andWith(prev);
            }
            Nfa temp;
            temp.createNfa(reg.substr(i, getNext(reg,i)-i+1));
            prev.thiseuqalsnfa(temp);
            i= getNext(reg,i);
           /* if(start==0&&prev.start!=0){
                thiseuqalsnfa(prev);
            }
            else if(start!=0&&prev.start!=0){
                andWith(prev);
            }*/
            ++i;
        }
        else if(reg[i]=='*'&&reg[i-1]!='\\'){
            prev.kleen();
            i++;
        }
        else if(reg[i]=='+'&&reg[i-1]!='\\'){
            prev.pKleen();
            i++;
        }
        else{
            if(reg[i]=='\\') {
                i++;
                continue;
            }
            else{
                if(start==0&&prev.start!=0){
                    thiseuqalsnfa(prev);
                }
                else if(start!=0&&prev.start!=0){
                    andWith(prev);
                }
                prev=Nfa(reg[i]);
                ++i;
            }
        }
    }
    if(start==0&&prev.start!=0){
        thiseuqalsnfa(prev);
    }
    else if(start!=0&&prev.start!=0){
        andWith(prev);
    }
}

void Nfa::createNfa(string reg) {
    start=0;
    end=0;
    while(reg[0]=='('&&getNext(reg,0)==reg.size()-1){
        reg=reg.substr(1,reg.size()-2);
    }
    vector<string>seperated;
    vector<Nfa>seperatedNfa;
    string str;
    int i=0;
    while(i<reg.size()){
        if(reg[i]=='|'&&reg[i-1]!='\\'){
            seperated.push_back(str);
            str="";
            ++i;
            continue;
        }
        else if(reg[i]!='('){
            str+=reg[i];
            ++i;
        }
        else if(reg[i]=='('){
            if(i>0){
                if(reg[i-1]!='\\'){
                    for(int j=i;j<=getNext(reg,i);++j){
                        str+=reg[j];

                    }
                    i=getNext(reg,i)+1;
                }
                else{
                    str+=reg[i];
                    i++;
                }
            }
            else{
                for(int j=i;j<=getNext(reg,i);++j){
                    str+=reg[j];

                }
                i=getNext(reg,i)+1;
            }
        }

    }
    seperated.push_back(str);
    for(int i=0;i<seperated.size();++i){
        if(containsor(seperated[i])){
            executeString(parenthesis(seperated[i]));
            seperatedNfa.push_back(getThis());
        } else{
            executeString(seperated[i]);
            seperatedNfa.push_back(getThis());
        }
    }
    if(seperatedNfa.size()==1)
        thiseuqalsnfa(seperatedNfa[0]);
    else
        thiseuqalsnfa(orAll(seperatedNfa));
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
    tags=tempo;
    start+=offsetAmnt;
    end+=offsetAmnt;

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




Nfa Nfa::orAll(vector<Nfa> in){
    int nstates=1;
    in[0].offset(1);
    nstates+=in[0].numberOfStates;
    in[0].addEdge(in[0].start,1,"$");
    string tg="("+in[0].tags[in[0].end]+")";
    for (int i = 1; i < in.size(); ++i) {
        in[i].offset(nstates);
        nstates+=in[i].numberOfStates;
        in[0].addEdge(in[i].start,1,"$");
        tg=tg+"|"+"("+in[i].tags[in[i].end]+")";
    }
    in[0].numberOfStates=nstates+1;
    for (int i = 0; i < in.size(); ++i) {
        in[0].addEdge(in[0].numberOfStates,in[i].end,"$");
    }
    for (int i = 1; i < in.size(); ++i) {
        Nfa second=in[i];
        for (map<int, map<string, vector<int>>>::iterator it = second.transitions.begin();it != second.transitions.end(); ++it) {
            in[0].transitions[it->first] = it->second;
        }
        for (int i = 0; i < second.accepting.size(); ++i) {
            in[0].accepting.push_back(second.accepting[i]);

        }
        for (map<int, string>::iterator it = second.tags.begin(); it != second.tags.end(); ++it) {
            in[0].tags[it->first] = it->second;
        }

    }
    in[0].start=1;
    in[0].accepting.push_back(in[0].numberOfStates);
    in[0].end=in[0].numberOfStates;
    start=1;
    in[0].tags[in[0].end]=tg;
    return in[0];

}


set<string> Nfa::getAlphabets() {
    set<string> alpha;
    for(auto i : transitions){
        for(auto j : i.second){
            alpha.insert(j.first);
        }
    }
    return alpha;
}

Nfa Nfa::getfromlist(vector<string>in){
    vector<Nfa> temp;
    for(auto i:in){
        Nfa tempo;
        tempo.createNfa(i);
        temp.push_back(tempo.getThis());
    }
    return orAll(temp);
}