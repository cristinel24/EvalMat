#include <iostream>
#include <fstream>


#define NMAX 1024
using namespace std;

ifstream fin("eval.in");
ofstream fout("eval.out");

#include "Structuri.h"
#include "Conversii.h"
#include "Arbore.h"
#include "string_m.h"
#include "Menu.h"


void back();
void init_coada(string, coada&);

int main()
{
    initwindow(screen_width, screen_height, "EvalMath");
    Menu();
    /*char s[100];
    strcpy(s, "x=sin(cos(14))");
    bool ok = check_variable(s);*/
    //back();
    return 0;
}
void back() {
    string x, xarb;
    getline(fin, x);
    xarb = x;
    if (x == "") {
        cout << "Sir inexistent!";
        exit(0);
    }
    try {
        parse(x);
        init_coada(x, infix);
        cout << valpostfix(infix);

        /* Pentru arbore
        coada infix, postfix;
        arb T = nullptr; string arr[NMAX]; coada postfix;
        init_coada_arb(xarb, infix);
        convInfix2Postfix_arb(infix, postfix);
        T = arb_gen(T, postfix);
        bfs(T, arr);*/
    }
    catch (invalid_argument& e) {
        cout << e.what();
    } 
    return;
}

