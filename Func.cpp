//
// Created by ydl on 18-6-16.
//

#include "Func.h"


Block::Block() = default;

Block::Block(int _id, bool ret = false) : {
    if (ret) id = -1;
    else {
        id = _id;
    }
    judge = false;
}

void Block::insert(assign as) {
    container.push_back(as);
}

void Block::insertjudge(string o, string o1, string o2, int t, int f, Func &parent) {
    op = o;
    op1 = o1;
    op2 = o2;
    tid = t;
    fid = f;
    judge = true;
    parent.tails[id].insert(t);
    parent.tails[id].insert(f);
    parent.heads[t].insert(id);
    parent.heads[f].insert(id);
}

void Block::insertgoto(int t, Func &parent) {
    tid = t;
    parent.tails[id].insert(t);
    parent.heads[t].insert(id);
}

void Block::insertret(string s) {
    ret = s;
}


void Func::insertsym(string s, int n) {
    symtbl.insert(make_pair(s, n));
}

void Func::insertblk(Block b, int n) {
    container[n] = b;
}

void Func::insertdecl(string s, string type) {
    decltbl.insert(make_pair(s, type));
}

void Func::insertpara(string s, string type) {
    parm.insert(make_pair(s,type));
}