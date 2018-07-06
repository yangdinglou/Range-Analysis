//
// Created by ydl on 18-6-16.
//

#ifndef PROJECT_PARSER_H
#define PROJECT_PARSER_H

#include "Func.h"
#include <iostream>
#include <sstream>

using namespace std;

vector<Func>
Parser(istream &cin) {
    vector<Func> ret;
    string tmp;
    bool Infunc = false;
    bool InBlock = false;
    Func tmpfunc;
    Block tmpblk;
    while (!cin.eof()) {
        getline(cin, tmp);
        if(tmp=="000")break;
        if (tmp == "")continue;
        stringstream ss(tmp);
        string label;
        ss >> label;
        if (label[0] == ';')continue;
        if (label=="foo"||label=="bar") {
            Infunc == true;
            tmpfunc = Func(label);
            char c;
            while (c = ss.get()) {
                if (c == '(') {
                    string s1, s2;
                    while (ss >> s1) {
                        if (s1 == ")")break;
                        ss >> s2;
                        char endc = s2[s2.size() - 1];
                        s2.resize(s2.size() - 1);
                        tmpfunc.insertpara(s2, s1);
                        if (endc == ')')break;
                    }
                    break;
                }
            }
            continue;
        }
        if (label == "{")continue;
        if (label == "}") {
            InBlock= false;
            Infunc = false;
            if ((!tmpfunc.parm.empty()) && tmpfunc.flag) {
                for (auto i:tmpfunc.parm) {
                    cout << i.first << "Range(l,r)" << endl;
                    float l, r;
                    cin >> l >> r;
                    tmpfunc.parmrange.insert(make_pair(i.first, section(l, r)));
                }
            }
            ret.push_back(tmpfunc);
            continue;
        }
        if (label == "int" || label == "float") {
            string declname;
            ss >> declname;
            declname.resize(declname.size() - 1);

            tmpfunc.insertdecl(declname, label);
            continue;
        }
        if (label == "<bb") {
            if (InBlock) {
                if(tmpblk.tid==0)
                {
                    tmpblk.insertgoto(tmpblk.id+1,tmpfunc);
                }
                tmpfunc.insertblk(tmpblk, tmpblk.id);
            }
            int n;
            ss >> n;
            tmpblk = Block(n, false);
            InBlock = true;
            continue;
        }
        if (label[0] == '<' && label[1] == 'L') {
            if(tmpblk.tid==0)
                tmpblk.insertgoto(1,tmpfunc);
            tmpfunc.insertblk(tmpblk, tmpblk.id);
            tmpblk = Block(1, true);
            cin>>tmp;
            cin>>tmp;
            tmp.resize(tmp.size()-1);
            tmpblk.insertret(tmp);
            tmpfunc.insertblk(tmpblk,1);
            continue;
        }
        if (InBlock) {
            if(label=="return;")
            {
                tmpfunc.voidf=true;
            }
            else if (label == "#") {
                string name, op1, op2;
                int f1, f2;
                ss >> name;
                int flag = 0;
                char tmpch;
                while (1) {
                    tmpch = ss.get();
                    if (tmpch == '<')
                    {
                        flag = 1;
                        continue;
                    }
                    if(flag==1&&tmpch!='(')
                    {
                        op1.push_back(tmpch);
                        continue;
                    }
                    if(flag==1&&tmpch=='(')
                    {
                        flag=-1;
                        continue;
                    }
                    if(flag==-1&&tmpch==' ')
                    {
                        flag=2;
                        continue;
                    }
                    if(flag==2&&tmpch!='(')
                    {
                        op2.push_back(tmpch);
                        continue;
                    }
                    if(flag==2&&tmpch=='(')
                    {
                        break;
                    }

                }
                tmpblk.insert(assign(name, op1, op2));
                tmpfunc.insertsym(name,tmpblk.id);
            }//PHI
            else if (label == "if") {
                string o, o1, o2;
                int t, f;
                char tmpch;
                int flag = 0;
                int cnt = 0;
                while (1) {
                    tmpch = ss.get();
                    if (tmpch == '(' && flag == 0) {
                        flag = 1;
                        continue;
                    }
                    if (flag == 1) {
                        if (tmpch == ' ') {
                            flag = -1;
                        } else {
                            o1.push_back(tmpch);
                        }
                        continue;
                    }
                    if (flag == -1) {
                        if (tmpch == ' ') {
                            flag = 2;
                        } else {
                            o.push_back(tmpch);
                        }
                        continue;
                    }
                    if (flag == 2) {
                        if (tmpch == ')' && cnt == 0)
                            break;
                        if (tmpch == '(')
                            cnt++;
                        else {
                            if(tmpch==')')cnt--;
                            else o2.push_back(tmpch);
                        }
                    }
                }
                while (cin>>tmp)
                {
                    if(tmp=="<bb") {
                        cin >> t;
                        break;
                    }
                }
                getline(cin, tmp);

                getline(cin, tmp);//else
                while (cin>>tmp)
                {
                    if(tmp=="<bb") {
                        cin >> f;
                        break;
                    }
                }
                getline(cin, tmp);

                tmpblk.insertjudge(o, o1, o2, t, f, tmpfunc);

            }//if goto else goto
            else if (label == "goto") {
                string eat;
                ss >> eat;
                int n;
                ss >> n;
                tmpblk.insertgoto(n, tmpfunc);
            }//goto
            else {
                string name(label), op, op1, op2;
                int flag=1;
                while (flag!=-1)
                {
                    switch (flag)
                    {
                        case 1:
                        {
                            ss>>op1;
                            ss>>op1;
                            if(op1.at(op1.size()-1)==';') {
                                op1.resize(op1.size() - 1);
                                flag=-1;
                                break;
                            }
                            flag=2;
                            break;
                        }
                        case 2:
                        {
                            ss>>op;
                            ss>>op2;
                            op2.resize(op2.size()-1);
                            flag=-1;
                            break;
                        }

                    }
                }
                if(op=="")
                {
                    tmpblk.insert(assign(name,op1));
                } else{
                    tmpblk.insert(assign(name,op,op1,op2));
                }
                tmpfunc.insertsym(name,tmpblk.id);
            }// x = y (+ z)
        }
    }return ret;
};


#endif //PROJECT_PARSER_H
