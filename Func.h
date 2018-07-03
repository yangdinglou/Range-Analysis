//
// Created by ydl on 18-6-16.
//

#ifndef PROJECT_FUNC_H
#define PROJECT_FUNC_H

#include <set>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "section.h"

using namespace std;

class assign {//赋值
    bool PHI;
    bool flag;//有op
    string name;
    string op;
    string op1, op2;
public:
    assign(string n, string o, string o1, string o2) : name(n), op(o), op1(o1), op2(o2), PHI(false), flag(true) {};

    assign(string n, string o1, string o2) : name(n), op1(o1), op2(o2), PHI(true), flag(false) {};

    assign(string n, string o1) : name(n), op1(o1), flag(false) {};

    void print()
    {
        if(PHI)
        {
            cout<<name<<"=PHI"<<op1<<","<<op2<<endl;
        }
        else if(flag)
        {
            cout<<name<<"="<<op1<<op<<op2<<endl;
        }
        else
        {
            cout<<name<<"="<<op1<<endl;
        }
    }
};

class Func;

class Block {//bb
    vector<assign> container;
    bool judge;
    string op, op1, op2;
    int tid, fid;
    string ret;
public:
    int id;

    Block() = default;

    Block(int _id, bool ret = false);

    void insert(assign as);

    void insertjudge(string o, string o1, string o2, int t, int f, Func &parent);

    void insertgoto(int t, Func &parent);

    void insertret(string s);

    void print(){
        for(auto i:container)
        {
            i.print();
        }
        if(judge) {
            cout << op1 << op << op2 << endl;
            cout << "True:" << tid << "\n" << "False:" << fid << "\n";
        }
        else
            cout<<"Goto"<<tid<<endl;
        if(ret!="")
            cout<<"return "<<ret<<endl;
    }
};

class Func {
    Block container[10];
    map<string, int> symtbl;//symbol->block
    map<string, string> decltbl;//decl->type

    bool flag;
    string name;
public:
    map<string, string> parm;//parm->type
    map<string, section> parmrange;
    set<int> tails[10];
    set<int> heads[10];

    Func() = default;

    Func(string n) : name(n) {
        if (name == "foo") {
            flag = true;
        } else {
            flag = false;
        }
    };

    void insertsym(string s, int n);

    void insertblk(Block b, int n);

    void insertdecl(string s, string type);

    void insertpara(string s, string type);


    void print()
    {
        for(int i=0;i<10;++i)
            if(container[i].id!=0)
            {
                container[i].print();
            }
    }
};


#endif //PROJECT_FUNC_H
