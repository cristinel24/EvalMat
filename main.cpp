#include <iostream>
#include <fstream>
#define NMAX 1024
using namespace std;
#include "Structuri.h"
#include "Conversii.h"
#include "Arbore.h"
#include "string_m.h"
#include "Menu.h"

ifstream fin("eval.in");
ofstream fout("eval.out");
void back();
void init_coada(string, coada&);

int main()
{
    back();
    //Menu();
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
    }
    catch (int e) {
        switch(e) {
            case -1: cout << "Impartire la zero!"; break;
            case -2: cout << "Radical din numar negativ!"; break;
            case -3: cout << "Logaritm din numar negativ sau zero!"; break;
            default: cout << "Eroare"; break;
        }
    } 
    return;
}

