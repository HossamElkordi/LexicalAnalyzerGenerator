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


int Nfa::getStart() {
    return start;
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
    string tg=tags[end];
    tg+="*";
    offset(1);
    numberOfStates+=2;
    addEdge(start,1,"$");
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
    string tg=tags[end];
    tg+="+";
    offset(1);
    numberOfStates+=2;
    addEdge(start,1,"$");
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

bool isSep(char a){
    if(a=='-'||a=='|'||a=='+'||a=='*'||a=='('||a==')'||a=='\\'){
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
string Nfa::parenthesis(string reg) {
    //_________________stage two parenthesising for the kleen closure and or_________
    for(int i=1;i<reg.size();i++){
        if((reg[i]=='*'||reg[i]=='+')&&reg[i-1]!='\\'){
            if(i==1){
                reg.insert(i+1,")");
                reg.insert(i,")");
                i++;
                reg.insert(i-2,"((");
                i+=2;
            }
            else if (reg[i-1]==')'&&reg[i-2]!='\\'){
                int j=i-2;
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
                reg.insert(i+1,")");

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
    for(int i=1;i<reg.size();i++){
        if(reg[i]=='|'&&reg[i-1]!='\\'){
            if(i>1){
                if(reg[i-1]==')'){
                    int j=i-1;
                    while(j>=0){
                        int count=-1;
                        if(reg[j]!='('){
                            if(reg[j]==')'){++count;}
                            --j;
                        }
                        else if(j!=0){
                            if(reg[j-1]=='\\'){
                                --j;
                            }
                            else{
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
                        }
                        else{
                            reg.insert(j,"(");
                            ++i;
                            break;
                        }
                    }
                }
                else{
                    reg.insert(i,")");
                    ++i;
                    reg.insert(i-2,"((");
                    i+=2;
                }

            }
            else{
                reg.insert(i,")");
                ++i;
                reg.insert(0,"((");
                i+=2;
            }
            if(i<reg.size()-1){
                if(reg[i+1]=='('){
                    int j=i+2;
                    int count=0;
                    while(j<reg.size()){
                        if(reg[j]==')'&&reg[j-1]!='\\'){
                            if(count==0) {
                                reg.insert(j + 1, ")");
                                break;
                            }
                            else{
                                --count;++j;
                            }
                        }
                        else if(reg[j]=='('&&reg[j-1]!='\\'){
                            ++count;
                            ++j;
                        }
                        else{++j;}
                    }
                }
                else{
                    reg.insert(i+2,"))");
                    reg.insert(i+1,"(");
                }
            }
        }
    }
    return reg;
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

void Nfa::execute(char op,string operand){
    if(op=='+')
        pKleen();
    else if(op=='*')
        kleen();
    else if(op=='|')
        orWith(temporaryMap[operand]);
    else
        andWith(temporaryMap[operand]);
}
bool isoperation(char a ){
    return (a=='*'||a=='+'||a=='|'||a=='*');
}


void Nfa::createNfa(string reg,string name,bool doParenthesis) {
//____________________stage one:preparation______________________________________
//the next for loop creates an Nfa from each char that is not a separator or an operator
//in preparation for the next stage
    for(int i=0;i<reg.size();i++){
        string str;
        str+=reg[i];
        bool con=(!isSep(reg[i]))||(i>0&&(isSep(reg[i])&&reg[i-1]=='\\'));
        if(con){
            if(!existsInTempMap(str))
                temporaryMap[str]=Nfa(reg[i]);
        }
    }
//_________________end of stage one______________________________________________
    if (doParenthesis){reg= parenthesis(reg);}

//_________________stage three:looking for parenthesis_________
    for(int i=0;i<reg.size();i++){
        if((i>0&&reg[i]=='('&&reg[i-1]!='\\')||(i==0&&reg[i]=='(')){
            int end= getNext(reg,i);
            /*while(reg[end+1+i]!=')'||reg[end+i]=='\\'){
                ++end;
            }*/
            Nfa newnfa=Nfa();
            newnfa.createNfa(reg.substr(i+1,end-i-1)," ", false);
            temporaryMap[reg.substr(i,end+1)]=newnfa.getThis();
        }

    }
//_________________end of stage three___________________________
//tagmee3
    start=1;
    end=1;
    numberOfStates=1;
    char op='x';
    for (int i = 0; i < reg.size(); ++i) {
        char currentop=op;
        string operand="";
        if(reg[i]=='\\')
            continue;
        if(!isoperation(reg[i])){
            int end=getNext(reg,i);
            operand=reg.substr(i,end-i+1);
            op='x';
            i=end;
            execute(currentop,operand);
        }
        else if(reg[i-1]=='\\'){
            operand=reg.substr(i,1);
            op='x';
            execute(currentop,operand);
        }
        else{
            if(reg[i]=='*')
                execute('*'," ");
            else if(reg[i]=='+')
                execute('+'," ");
            else
                op=reg[i];
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

