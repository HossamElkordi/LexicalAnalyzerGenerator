//
// Created by hossam on 07/05/2021.
//

#include "MinimizedDfa.h"

void minimizeDfa(map<set<int>, map<string, set<int>>>* graph, map<set<int>, string>* dfaAccepted, set<string> alphabet, set<int>* start){
    set<int> dfaTable[graph->size()][alphabet.size()];
    map<set<int>, int> states;
    string inputs[alphabet.size()];
    map<set<int>, map<string, set<int>>>::iterator itr;
    set<string>::iterator itr1;
    int i=0;
    for (itr = graph->begin(); itr != graph->end(); ++itr){
        states.insert(pair<set<int>, int>(itr->first, i));
        ++i;
    }
    i=0;
    for (itr1 = alphabet.begin(); itr1 != alphabet.end(); ++itr1){
        inputs[i] = *itr1;
        ++i;
    }
    int row = 0;
    for (itr = graph->begin(); itr != graph->end(); ++itr){
        for(i=0;i<alphabet.size();++i){
            dfaTable[row][i] = itr->second[inputs[i]];
        }
        ++row;
    }

    set<set<int>> finalStates;
    set<set<int>> remainingStates;
    set<string> s;
    set<string>::iterator it;
    set<set<set<int>>> temp;
    for (itr = graph->begin(); itr != graph->end(); ++itr){
        if(dfaAccepted->find(itr->first) != dfaAccepted->end()){
            s.insert((*dfaAccepted)[itr->first]);
        }else{
            remainingStates.insert(itr->first);
        }
    }
    for (it = s.begin(); it != s.end(); ++it){
        set<set<int>> l;
        for (itr = graph->begin(); itr != graph->end(); ++itr){
            if(dfaAccepted->find(itr->first) != dfaAccepted->end() && (*dfaAccepted)[itr->first]==(*it)){
                l.insert(itr->first);
            }
        }
        temp.insert(l);
    }

    vector<set<set<set<int>>>> partitions;
    temp.insert(remainingStates);
    partitions.push_back(temp);
    bool finish = false;
    set<set<set<int>>>::iterator sss;
    set<set<int>>::iterator ss;
    int p=0, k=-1;
    while(!finish){
        int groups[graph->size()][alphabet.size()];
        for(i=0;i<graph->size();++i){
            for(int j=0;j<alphabet.size();++j){
                groups[i][j]=-1;
            }
        }
        for (sss = partitions[p].begin(); sss != partitions[p].end(); ++sss){
            ++k;
            for(i=0;i<graph->size();++i){
                for(int j=0;j<alphabet.size();++j){
                    if((*sss).find(dfaTable[i][j]) != (*sss).end()){
                        groups[i][j]=k;
                    }
                }
            }
        }
        k=-1;
        set<set<set<int>>> final;
        for (sss = partitions[p].begin(); sss != partitions[p].end(); ++sss){
            vector<vector<set<int>>> temporary;
            bool identical=true;
            for (ss = (*sss).begin(); ss != (*sss).end(); ++ss){
                if(temporary.empty()){
                    vector<set<int>> v;
                    v.push_back(*ss);
                    temporary.push_back(v);
                }else{
                    for(i=0;i<temporary.size();++i){
                        for(int x=0;x<alphabet.size();++x){
                            if(groups[states[temporary[i][0]]][x] != groups[states[*ss]][x]){
                                identical=false;
                                break;
                            }
                        }
                        if(identical){
                            temporary[i].push_back(*ss);
                            break;
                        }
                    }
                    if(!identical){
                        identical=true;
                        vector<set<int>> v;
                        v.push_back(*ss);
                        temporary.push_back(v);
                    }
                }
            }
            for(i=0;i<temporary.size();++i){
                set<set<int>> f;
                for(auto & j : temporary[i]){
                    f.insert(j);
                }
                final.insert(f);
            }
        }
        partitions.push_back(final);
        ++p;
        if(p!=0 && partitions[p]==partitions[p-1]){
            finish=true;
        }
    }

    for (sss = partitions[p].begin(); sss != partitions[p].end(); ++sss){
        if((*sss).find(*start) != (*sss).end()){
            *start=*(*sss).begin();
            break;
        }
    }

    map<set<int>, set<int>> mappingDeleted;
    set<set<int>> essentials;
    for (sss = partitions[p].begin(); sss != partitions[p].end(); ++sss){
        if((*sss).size() == 1){
            essentials.insert(*(*sss).begin());
        }else{
            set<int> g;
            for (ss = (*sss).begin(); ss != (*sss).end(); ++ss){
                if(ss == (*sss).begin()){
                    g=*ss;
                    essentials.insert(g);
                }else{
                    mappingDeleted[*ss] = g;
                }
            }
        }
    }

    map<set<int>, set<int>>::iterator e;
    for(e=mappingDeleted.begin(); e!=mappingDeleted.end(); ++e){
        graph->erase(e->first);
        if(dfaAccepted->find(e->first) != dfaAccepted->end()){
            dfaAccepted->erase(e->first);
        }
    }

    for (itr = graph->begin(); itr != graph->end(); ++itr){
        for(i=0; i<alphabet.size(); ++i){
            if(mappingDeleted.find(itr->second[inputs[i]]) != mappingDeleted.end()){
                itr->second[inputs[i]] = mappingDeleted[itr->second[inputs[i]]];
            }
        }
    }
}