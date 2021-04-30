//
// Created by hossam on 29/04/2021.
//

#ifndef LEXICALANALYZERGENERATOR_STATE_H
#define LEXICALANALYZERGENERATOR_STATE_H

#include <string>
#include <list>
#include <set>
#include <map>

using namespace std;

class State{
    private:
        list<int> subsetState;
        map<char, set<int>> trans;
        bool isAccepting;
        string type;

    public:
        State(int sub);
        State();
        bool getIsAcc();
        void setAcc(bool acc);
        string getType();
        void setType(string token_type);
        void addSub(int sub);
        void addTrans(char input, int to);
};

#endif //LEXICALANALYZERGENERATOR_STATE_H
