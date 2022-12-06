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
    /*initwindow(screen_width, screen_height, "EvalMath");
    Menu();*/
    back();
    return 0;
}
void back() {
    string x;
    getline(fin, x);
    if (x == "") {
        cout << "Sir inexistent!";
        exit(0);
    }
    try {
        parse(x);
        init_coada(x, infix);
        cout << valpostfix(infix);

        /// Pentru arbore

        /*arb T = nullptr; string arr[NMAX]; coada postfix;
        init_coada_arb(x, infix);
        convInfix2Postfix_arb(infix, postfix);
        T = arb_gen(T, postfix);
        bfs(T, arr);*/
    }
    catch (int e) {
        switch(e) {
            case -1: cout << "Impartire la zero!"; break;
            case -2: cout << "Radical din numar negativ!"; break;
            case -3: cout << "Logaritm din numar negativ sau zero!"; break;
            case -4: cout << "Operator inexistent!"; break;
            default: cout << "Eroare"; break;
        }
    } 
    return;
}

