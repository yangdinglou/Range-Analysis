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
Parser() {
    vector<Func> ret;
    string tmp;
    bool Infunc= false;
    bool InBlock= false;
    Func tmpfunc;
    Block tmpblk;
    while (!cin.eof())
    {
        getline(cin,tmp);
        if(tmp=="")continue;
        stringstream ss(tmp);
        string label;
        ss<<label;
        if(label[0]==';')continue;
        if(/*!Infunc*/)
        {
            Infunc== true;
            tmpfunc=Func(label);
            char c;
            while (c=ss.get())
            {
                if(c=='(')
                {
                    string s1,s2;
                    while (cin>>s1)
                    {
                        if(s1==")")break;
                        cin>>s2;
                        char endc=s2[s2.size()-1];
                        s2.resize(s2.size()-1);
                        tmpfunc.insertpara(s2,s1);
                        if(endc==')')break;
                    }
                }
            }
            continue;
        }
        if(label=="{")continue;
        if(label=="}"){
            Infunc= false;
            if(!tmpfunc.parm.empty())
            {
                for(auto i:tmpfunc.parm)
                {
                    cout<<i.first<<"Range(l,r)"<<endl;
                    if(i.second=="int")

                }
            }
            ret.push_back(tmpfunc);
        }
        if(label=="int"||label=="float"){
            string declname;
            ss<<declname;
            declname.resize(declname.size()-1);

            tmpfunc.insertdecl(declname,label);
            continue;
        }
        if(label=="<bb")
        {
            if(InBlock)
                tmpfunc.insertblk(tmpblk,tmpblk.id);
            int n;
            ss<<n;
            tmpblk=Block(n);
            InBlock= true;
            continue;
        }
        if(label[0]=='<'&&label[1]=='L')
        {
            tmpfunc.insertblk(tmpblk,tmpblk.id);
            tmpblk=Block(0, true);
            continue;
        }
        if(InBlock)
        {
            if(label=="#"){

            }//PHI
            else if(label=="if"){

            }//if goto else goto
            else if(label=="goto")
            {
                string eat;
                ss<<eat;
                int n;
                ss<<n;
                tmpblk.insertgoto(n,tmpfunc);
            }//goto
            else{

            }// x = y (+ z)
        }
    }
};


#endif //PROJECT_PARSER_H
