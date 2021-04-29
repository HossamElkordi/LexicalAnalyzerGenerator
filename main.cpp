#include <iostream>
#include <list>
#include <regex>

using namespace std;

int main() {
    cout << "Hello, World!" << std::endl;
    return 0;
}

void split(string str, string seperator, list<string> * strings){
    regex rgx(seperator);
    sregex_token_iterator iter(str.begin(),str.end(), rgx, -1);
    sregex_token_iterator end;
    for ( ; iter != end; ++iter)
        if(*iter!="")
            strings->push_back(*iter);
}