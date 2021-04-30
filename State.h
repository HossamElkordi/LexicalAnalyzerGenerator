//
// Created by hossam on 29/04/2021.
//

#ifndef LEXICALANALYZERGENERATOR_STATE_H
#define LEXICALANALYZERGENERATOR_STATE_H

#include <string>
#include <list>

using namespace std;

class State{
    private:
        bool isAccepting;
        string type;

    public:
        State(bool accepting, string token_type);
        State();
        bool getIsAcc();
        void setAcc(bool acc);
        string getType();
        void setType(string token_type);
        void addTrans(State to,string weight);

};

#endif //LEXICALANALYZERGENERATOR_STATE_H
