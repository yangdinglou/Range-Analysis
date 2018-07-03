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

template<typename T>
class section {

    T l, r;
    T inf;
public:
    section(T l_, T r_) : l(l_), r(r_) {
        if (is_integral<T>::value) {
            inf = INT_MAX;
        } else {
            inf = FLT_MAX;
        }
    }

    bool isEmpty() {
        return l > r;
    }

    friend section operator+(const section &s1, const section &s2) {
        return section(add(s1.l, s2.l), add(s1.r, s2.r));
    }

    friend section operator-(const section &s1, const section &s2) {
        return section(minus(s1.l, s2.r), minus(s1.r, s2.l));
    }

    friend section operator*(const section &s1, const section &s2) {
        set<decltype(s1.l)> tmp;
        tmp.insert(multi(s1.l, s2.l));
        tmp.insert(multi(s1.l, s2.r));
        tmp.insert(multi(s1.r, s2.l));
        tmp.insert(multi(s1.r, s2.r));
        return section(*(tmp.begin()));
    }
    friend section operator/(const section &s1, const section &s2){
        return s1*section((T)1/s2.l,(T)1/s2.r);
    }
    friend section uni(const section &s1, const section &s2) {
        return section(max(s1.l, s2.l), min(s1.r, s2.r));
    }

    friend section inter(const section &s1, const section &s2) {
        return section(min(s1.l, s2.l), max(s1.r, s2.r));
    }

    section multiadd(T a, T b) {
        int x1 = add(b, multi(a, l));
        int x2 = add(b, multi(a, r));
        return section(min(x1, x2), max(x1, x2));
    }
};

template<typename T>
T add(T a, T b) {
    if (is_integral<T>::value) {
        if (INT_MAX - max(a, b) < min(a, b))
            return INT_MAX;
        else
            return a + b;
    } else {
        if (FLT_MAX - max(a, b) < min(a, b))
            return FLT_MAX;
        else
            return a + b;
    }
}

template<typename T>
T minus(T a, T b) {
    return add(a, -b);
}

template<typename T>
T multi(T a, T b) {
    if (max(a, b) == 0)return 0;
    if (is_integral<T>::value) {
        if (INT_MAX / max(a, b) < min(a, b))
            return INT_MAX;
        else
            return a * b;
    } else {
        if (FLT_MAX / max(a, b) < min(a, b))
            return FLT_MAX;
        else
            return a * b;
    }
}

template<typename T>
T divi(T a, T b) {
    return a / b;
}


#endif //PROJECT_SECTION_H
