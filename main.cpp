#include <iostream>
#include "Parser.h"
#include "scc.h"

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
    auto tmp=Parser(cin);
    scc test(tmp[0]);
    return 0;
}
