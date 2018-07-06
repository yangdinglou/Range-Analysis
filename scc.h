//
// Created by ydl on 18-7-5.
//

#ifndef PROJECT_SCC_H
#define PROJECT_SCC_H

#include "Func.h"
#include <queue>

set<int> essa(Func &func);
class Node;
class scc {
    map<string,int> symbolid;
    vector<string> symbol;
    vector<assign> summary;
    vector<set<int> >out,dashout;
public:
    scc(Func& func);

};

class Node{
    int type;//1Val 2Constraint 3Section
    string name;
    char op;
    section sec;
    int id;
    set<int> in,out;
    set<int> dashin,dashout;
};

#endif //PROJECT_SCC_H
