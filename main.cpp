#include <iostream>
#include "Func.h"
#include "section.h"

using namespace std;

class sentence {
public:
    enum type {
        HEAD,
        DECL,
        ASSIGN,
        PHI,
        RET,
        IF, ELSE,
        GOTO
    };
};




int main() {
    cout << FLT_MAX;
    return 0;
}
