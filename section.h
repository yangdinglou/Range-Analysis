//
// Created by ydl on 18-6-16.
//

#ifndef PROJECT_SECTION_H
#define PROJECT_SECTION_H

#include <type_traits>
#include <climits>
#include <cfloat>
#include <cmath>

using namespace std;

static float add(float a, float b) {

    if (FLT_MAX - max(a, b) < min(a, b))
        return FLT_MAX;
    else
        return a + b;

}


static float multi(float a, float b) {
    if (max(a, b) == 0)return 0;

    if (FLT_MAX / max(a, b) < min(a, b))
        return FLT_MAX;
    else
        return a * b;

}

static float divi(float a, float b) {
    return a / b;
}

class section {
    float l, r;
    float inf;
public:
    void print()
    {
        cout<<"{"<<l<<" , "<<r<<"}"<<endl;
    }
    section() = default;

    section(float num) : l(num), r(num) {
        inf = FLT_MAX;
    }

    section(float l_, float r_) : l(l_), r(r_) {
        inf = FLT_MAX;
    }

    section(string op1, string op, float num, string tp, bool judge) {
        inf = FLT_MAX;
        if (tp == "int") {
            if (op == "<") {
                switch (judge) {
                    case true://op1t
                    {
                        l = -inf;
                        r = num - 1;
                        break;
                    }
                    case false://op1f
                    {
                        l = num;
                        r = inf;
                        break;
                    }
                }
            } else if (op == "<=") {
                switch (judge) {
                    case true://op1t
                    {
                        l = -inf;
                        r = num;
                        break;
                    }
                    case false://op1f
                    {
                        l = num + 1;
                        r = inf;
                        break;
                    }
                }
            }else if(op=="=="){
                switch (judge)
                {
                    case true://op1t
                    {
                        l=num;
                        r=num;
                        break;
                    }
                    case false://op1f
                    {
                        l=-inf;
                        r=inf;
                        break;
                    }
                }
            } else{
                switch (judge)
                {
                    case false://op1f
                    {
                        l=num;
                        r=num;
                        break;
                    }
                    case true://op1t
                    {
                        l=-inf;
                        r=inf;
                        break;
                    }
                }
            }
        } else{
            if (op == "<="||op=="<") {
                switch (judge) {
                    case true://op1t
                    {
                        l = -inf;
                        r = num;
                        break;
                    }
                    case false://op1f
                    {
                        l = num;
                        r = inf;
                        break;
                    }
                }
            }else if(op=="=="){
                switch (judge)
                {
                    case true://op1t
                    {
                        l=num;
                        r=num;
                        break;
                    }
                    case false://op1f
                    {
                        l=-inf;
                        r=inf;
                        break;
                    }
                }
            } else{
                switch (judge)
                {
                    case false://op1f
                    {
                        l=num;
                        r=num;
                        break;
                    }
                    case true://op1t
                    {
                        l=-inf;
                        r=inf;
                        break;
                    }
                }
            }
        }
    }

    bool isEmpty() {
        return l > r;
    }

    friend section operator+(const section &s1, const section &s2) {
        return section(add(s1.l, s2.l), add(s1.r, s2.r));
    }

    friend section operator-(const section &s1, const section &s2) {
        return section(add(s1.l, -s2.r), add(s1.r, -s2.l));
    }

    friend section operator*(const section &s1, const section &s2) {
        set<float> tmp;
        tmp.insert(multi(s1.l, s2.l));
        tmp.insert(multi(s1.l, s2.r));
        tmp.insert(multi(s1.r, s2.l));
        tmp.insert(multi(s1.r, s2.r));
        return section(*(tmp.begin()), *(tmp.rbegin()));
    }

    friend section operator/(const section &s1, const section &s2) {
        return s1 * section((float) 1 / s2.l, (float) 1 / s2.r);
    }

    friend section uni(const section &s1, const section &s2) {
        return section(max(s1.l, s2.l), min(s1.r, s2.r));
    }

    friend section inter(const section &s1, const section &s2) {
        return section(min(s1.l, s2.l), max(s1.r, s2.r));
    }

    section multiadd(float a, float b) {
        float x1 = add(b, multi(a, l));
        float x2 = add(b, multi(a, r));
        return section(min(x1, x2), max(x1, x2));
    }
};


#endif //PROJECT_SECTION_H
