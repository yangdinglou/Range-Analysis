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

class infsection {
    int type;//1 linf 2 rinf 3inf 4ftft
    string ft;
    int constant;
public:
    infsection() = default;

    infsection(string op1, string op, string op2, string tp, int ret)//ret0-3
    {
        if (tp == "int") {
            if (op == "<") {
                switch (ret) {
                    case 0://op1f
                    {
                        type = 2;
                        ft = op2;
                        constant = 0;
                        break;
                    }
                    case 1://op2f
                    {
                        type = 1;
                        ft = op1;
                        constant = 0;
                        break;
                    }
                    case 2://op1t
                    {
                        type = 1;
                        ft = op2;
                        constant = -1;
                        break;
                    }
                    case 3://
                    {
                        type = 2;
                        ft = op1;
                        constant = 1;
                        break;
                    }
                }
            } else if (op == "<=") {
                switch (ret) {
                    case 0://op1f
                    {
                        type = 2;
                        ft = op2;
                        constant = 1;
                        break;
                    }
                    case 1://op2f
                    {
                        type = 1;
                        ft = op1;
                        constant = -1;
                        break;
                    }
                    case 2://op1t
                    {
                        type = 1;
                        ft = op2;
                        constant = 0;
                        break;
                    }
                    case 3://
                    {
                        type = 2;
                        ft = op1;
                        constant = 0;
                        break;
                    }
                }
            } else if (op == "==") {
                switch (ret) {
                    case 0://op1f
                    {
                        type = 3;
                        break;
                    }
                    case 1://op2f
                    {
                        type = 3;
                        break;
                    }
                    case 2://op1t
                    {
                        type = 4;
                        ft = op2;
                        break;
                    }
                    case 3://op2t
                    {
                        type = 4;
                        ft = op1;
                        break;
                    }
                }
            } else//!=
            {
                switch (ret) {
                    case 0://op1f
                    {
                        type = 4;
                        ft = op2;
                        break;
                    }
                    case 1://op2f
                    {
                        type = 4;
                        ft = op1;
                        break;
                    }
                    case 2://op1t
                    {
                        type = 3;
                        break;
                    }
                    case 3://op2t
                    {
                        type = 3;
                        break;
                    }
                }
            }
        } else {
            if (op == "<=" || op == "<") {
                switch (ret) {
                    case 0://op1f
                    {
                        type = 2;
                        ft = op2;
                        constant = 0;
                        break;
                    }
                    case 1://op2f
                    {
                        type = 1;
                        ft = op1;
                        constant = 0;
                        break;
                    }
                    case 2://op1t
                    {
                        type = 1;
                        ft = op2;
                        constant = 0;
                        break;
                    }
                    case 3://
                    {
                        type = 2;
                        ft = op1;
                        constant = 0;
                        break;
                    }
                }
            } else if (op == "==") {
                switch (ret) {
                    case 0://op1f
                    {
                        type = 3;
                        break;
                    }
                    case 1://op2f
                    {
                        type = 3;
                        break;
                    }
                    case 2://op1t
                    {
                        type = 4;
                        ft = op2;
                        break;
                    }
                    case 3://op2t
                    {
                        type = 4;
                        ft = op1;
                        break;
                    }
                }
            } else//!=
            {
                switch (ret) {
                    case 0://op1f
                    {
                        type = 4;
                        ft = op2;
                        break;
                    }
                    case 1://op2f
                    {
                        type = 4;
                        ft = op1;
                        break;
                    }
                    case 2://op1t
                    {
                        type = 3;
                        break;
                    }
                    case 3://op2t
                    {
                        type = 3;
                        break;
                    }
                }
            }
        }
    }
    void print()
    {
        switch(type)
        {
            case 1:
            {
                cout<<"{-inf,ft("<<ft<<")}"<<endl;
                break;
            }
            case 2:
            {
                cout<<"{ft("<<ft<<"),+inf}"<<endl;
                break;
            }
            case 3:
            {
                cout<<"{-inf,+inf}"<<endl;
                break;
            }
            case 4:
            {
                cout<<"{ft("<<ft<<")}"<<endl;
                break;
            }
        }
    }
};

class assign {//赋值
public:
    int type;//0const 1singleop 2doubleop 3opconst 4PHI 5sec 6infsec
    string name;
    float num;
    string op;
    string op1, op2;
    section sec;
    infsection infsec;

    assign(string n, string o, string o1, string o2) : name(n), op(o), op1(o1), op2(o2) {

        try {
            float tmp = stof(op2);
            type = 3;
            num = tmp;
        } catch (std::invalid_argument) {
            type = 2;
        }
    };

    assign(string n, string o1, string o2) : name(n), op1(o1), op2(o2) {
        type = 4;
    };

    assign(string n, string o1) : name(n), op1(o1) {
        try {
            float tmp = stof(op1);
            type = 0;
            num = tmp;
        } catch (std::invalid_argument) {
            type = 1;
        }
    };

    assign(string n, string o1, section _sec) : name(n), op1(o1), sec(_sec), type(5) {};

    assign(string n, string o1, infsection _infsec) : name(n), op1(o1), infsec(_infsec), type(6) {};

    void print() {
        cout << name << " = ";
        switch (type) {
            case 0: {
                cout << num << endl;
                break;
            }
            case 1: {
                cout << op1 << endl;
                break;
            }
            case 2: {
                cout << op1 << " " << op << " " << op2 << endl;
                break;
            }
            case 3: {
                cout << op1 << " " << op << " " << num << endl;
                break;
            }
            case 4: {
                cout << "PHI" << " " << op1 << " " << op2 << endl;
                break;
            }
            case 5: {
                cout << op1 << " U ";
                sec.print();
                break;
            }
            case 6: {
                cout << op1 << " ";
                infsec.print();
                break;
            }
        }
    }
};

class Func;

class Block {//bb
public:
    vector<assign> container;
    bool judge;
    string op, op1, op2;

    string ret;

    int tid, fid;
    int id;

    Block();

    Block(int _id, bool ret = false);

    void insert(assign as);

    void insertjudge(string o, string o1, string o2, int t, int f, Func &parent);

    void insertgoto(int t, Func &parent);

    void insertret(string s);

    void print() {
        for (auto i:container) {
            i.print();
        }
        if (judge) {
            cout << op1 << op << op2 << endl;
            cout << "True:" << tid << "\n" << "False:" << fid << "\n";
        } else
            cout << "Goto" << tid << endl;
        if (ret != "")
            cout << "return " << ret << endl;
    }
};

class Func {
public:
    Block container[15];
    map<string, int> symtbl;//symbol->block
    map<string, string> decltbl;//decl->type


    string name;

    map<string, string> parm;//parm->type
    map<string, section> parmrange;
    bool flag;
    bool voidf;
    set<int> tails[15];
    set<int> heads[15];

    Func() = default;

    Func(string n) : name(n) {
        if (name == "foo") {
            flag = true;
        } else {
            flag = false;
        }
        voidf = false;
    };

    void insertsym(string s, int n);

    void insertblk(Block b, int n);

    void insertdecl(string s, string type);

    void insertpara(string s, string type);


    void print() {
        for (int i = 0; i < 15; ++i)
            if (container[i].id != 0) {
                cout << container[i].id << endl;
                container[i].print();
                cout << "Tail";
                for (auto t:tails[i])
                    cout << t << ' ';
                cout << endl;
                cout << "Head";
                for (auto t:heads[i])
                    cout << t << ' ';
                cout << endl;
            }
        cout << "Symbol!" << endl;
        for (auto i:symtbl) {
            cout << i.first << " " << i.second << endl;
        }
        cout << "Decl!" << endl;
        for (auto i:decltbl) {
            cout << i.first << " " << i.second << endl;
        }
        cout << "Parm!" << endl;
        for (auto i:parm) {
            cout << i.first << " " << i.second << endl;
        }
    }
};


#endif //PROJECT_FUNC_H
