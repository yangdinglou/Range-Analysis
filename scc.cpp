//
// Created by ydl on 18-7-5.
//

#include "scc.h"
set<int> essa(Func &func)
{
    queue<int> flag;
    flag.push(2);
    set<int> havedone;
    havedone.insert(2);

    bool judge = false;
    while (!flag.empty()) {
        int tmpid = flag.front();
        flag.pop();
        if (tmpid != 1) {
            if (func.container[tmpid].judge) {
                float tmp;
                auto tid = func.container[tmpid].tid;
                auto fid = func.container[tmpid].fid;
                if(havedone.find(tid)==havedone.end())
                    flag.push(tid);
                if(havedone.find(fid)==havedone.end())
                    flag.push(fid);
                havedone.insert(tid);
                havedone.insert(fid);
                try {
                    tmp = stof(func.container[tmpid].op2);
                    auto tmpstr = func.container[tmpid].op1;
                    auto loc = tmpstr.find('_');
					auto symbol = loc == 0 ? tmpstr : tmpstr.substr(0, loc);
                    string tp;
                    auto findtp = func.decltbl.find(symbol);
                    if (findtp != func.decltbl.end()) {
                        tp = findtp->second;
                    } else {
                        auto findtp2 = func.parm.find(symbol);
                        tp = findtp2->second;
                    }
                    auto sect = section(tmpstr, func.container[tmpid].op, tmp, tp, true);
                    auto secf = section(tmpstr, func.container[tmpid].op, tmp, tp, false);
                    int tmptflag=0;
                    for (auto &i:func.container[tid].container) {
                        if (i.op1 == tmpstr) {
                            i.op1 = tmpstr + "t";
                            tmptflag++;
                        }
                        if (i.op2 == tmpstr) {
                            i.op2 = tmpstr + "t";
                            tmptflag++;
                        }
                    }
                    if(tmptflag!=0)
                        func.container[tid].container.push_back(assign(tmpstr + "t", tmpstr, sect));
                    int tmpfflag=0;
                    for (auto &i:func.container[fid].container) {
                        if (i.op1 == tmpstr) {
                            i.op1 = tmpstr + "f";
                            tmpfflag++;
                        }
                        if (i.op2 == tmpstr) {
                            i.op2 = tmpstr + "f";
                            tmpfflag++;
                        }
                    }
                    if(tmpfflag!=0)
                        func.container[fid].container.push_back(assign(tmpstr + "f", tmpstr, secf));

                } catch (...) {
                    auto tmpblk = func.container[tmpid];
                    auto tmpstr1=tmpblk.op1,tmpstr2=tmpblk.op2;
                    auto loc1 = tmpstr1.find('_');
					auto symbol = loc1 == 0 ? tmpstr1 : tmpstr1.substr(0, loc1);
                    string tp;
                    auto findtp = func.decltbl.find(symbol);
                    if (findtp != func.decltbl.end()) {
                        tp = findtp->second;
                    } else {
                        auto findtp2 = func.parm.find(symbol);
                        tp = findtp2->second;
                    }
                    auto op1f=infsection(tmpblk.op1, tmpblk.op, tmpblk.op2, tp, 0);
                    auto op2f=infsection(tmpblk.op1, tmpblk.op, tmpblk.op2, tp, 1);
                    auto op1t=infsection(tmpblk.op1, tmpblk.op, tmpblk.op2, tp, 2);
                    auto op2t=infsection(tmpblk.op1, tmpblk.op, tmpblk.op2, tp, 3);
                    int t1(0),t2(0);
                    for (auto &i:func.container[tid].container) {
                        if (i.op1 == tmpstr1){
                            i.op1 = tmpstr1 + "t";
                            ++t1;
                        }
                        if (i.op2 == tmpstr1) {
                            i.op2 = tmpstr1 + "t";
                            ++t1;
                        }
                        if (i.op1 == tmpstr2) {
                            i.op1 = tmpstr2 + "t";
                            ++t2;
                        }
                        if (i.op2 == tmpstr2) {
                            i.op2 = tmpstr2 + "t";
                            ++t2;
                        }
                    }
                    if(t1!=0)
                        func.container[tid].container.push_back(assign(tmpstr1 + "t", tmpstr1, op1t));
                    if(t2!=0)
                        func.container[tid].container.push_back(assign(tmpstr2 + "t", tmpstr2, op2t));
                    int f1(0),f2(0);
                    for (auto &i:func.container[fid].container) {
                        if (i.op1 == tmpstr1){
                            i.op1 = tmpstr1 + "f";
                            ++f1;
                        }
                        if (i.op2 == tmpstr1) {
                            i.op2 = tmpstr1 + "f";
                            ++f1;
                        }
                        if (i.op1 == tmpstr2) {
                            i.op1 = tmpstr2 + "f";
                            ++f2;
                        }
                        if (i.op2 == tmpstr2) {
                            i.op2 = tmpstr2 + "f";
                            ++f2;
                        }
                    }
                    if(f1!=0)
                        func.container[fid].container.push_back(assign(tmpstr1 + "f", tmpstr1, op1f));
                    if(f2!=0)
                        func.container[fid].container.push_back(assign(tmpstr2 + "f", tmpstr2, op2f));

                }

            } else{
                auto tid=func.container[tmpid].tid;
                if(havedone.find(tid)==havedone.end())
                    flag.push(tid);
                havedone.insert(tid);
            }
        }
    }

    return havedone;
}
scc::scc(Func &func) {
    auto blknum=essa(func);
    int id=0;
    for(auto i:blknum)
    {
        for(auto j:func.container[i].container)
        {
            symbol.push_back(j.name);
            symbolid.insert(make_pair(j.name,id));
            ++id;
			j.print();
            summary.push_back(j);
        }
    }
//    for(auto i=0;i<symbol.size();++i)
//    {
//        switch (summary.at(i).type)
//        {
//
//        }
//    }
}
