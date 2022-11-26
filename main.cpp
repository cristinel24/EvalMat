#include <iostream>
#include <fstream>
#define NMAX 1028
using namespace std;
#include "Structuri.h"
#include "Conversii.h"
#include "Menu.h"

ifstream fin("eval.in");
ofstream fout("eval.out");
void back();

int main()
{
    back();
    //Menu();
    return 0;
}
void back() {
    string x;
    fin >> x;
    for (int i = 0; i < x.size(); i++) {
        if (operand(string(1, x[i])))
            infix.push(string(1, x[i]));
        else {
            int start = i, lg = 0;
            while (x[i] >= '0' && x[i] <= '9' || x[i] == '.') { i++, lg++; }
            string nr = x.substr(start, lg); i--;
            infix.push(nr);
        }
    }
    try {
        cout << valpostfix(postfix);
    }
    catch (exception e) {
        cout << e.what();
    }
}