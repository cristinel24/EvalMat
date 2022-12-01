#pragma once

const double pi = 3.14159265;

void init_coada(string, coada&);
void spaces(string&);
void checkNegative(string&);
void trigo(string&);
void parse(string&);

void init_coada(string x, coada& infix) {
    string aux;
    for (int i = 0; i < x.size(); i++) {
        while (x[i] < '0' || x[i]>'9')
            aux += x[i++];
        if (aux != "" && esteOperator(aux))
        {
            infix.push(aux);
            aux = ""; i--;
        }
        else {
            int start = i, lg = 0;
            while (x[i] >= '0' && x[i] <= '9' || x[i] == '.') { i++, lg++; }
            string nr = x.substr(start, lg); i--;
            infix.push(nr);
        }
    }
}
void spaces(string& x) {
    string aux = "";
    for (int i = 0; i < x.size(); i++)
        if (x[i] != ' ')
            aux += x[i];
    x = aux;
}
void checkNegative(string& x) {
    int i;
    string aux = "";
    for (i = 0; i < x.size(); i++)
    {
        if (x[0] == '-') {
            aux = "0" + x;
        }
        else if (x[i] == '-' && x[i - 1] == '-') {
            aux = x.substr(0, i - 2);
            aux += x.substr(i, x.size() - i + 2);
        }
        else if (x[i] == '-' && esteOperator(string(1,x[i-1]))) {
            aux = x.substr(0, i);
            aux += "0";
            aux += x.substr(i, x.size() - i);
        }
        if (aux != "") x = aux;
    }
    //cout << x << '\n';
}
void trigo(string& x) {
    string functions[] = { "sin","cos","tg","round","sqrt","log10" ,"log2" ,"log" , "abs"};
    int size = 10; string aux;
    coada interior;
    checkNegative(x);
    for (int i = 0; i < size; i++) {
        int poz = x.find(functions[i]);
        if (poz > -1) {
            int start = poz + functions[i].size() + 1, paranteze = 1;
            while (paranteze) {
                if (x[start] == '(') paranteze++;
                else if (x[start] == ')') paranteze--;
                if (paranteze) aux += x[start++];
            }
            //cout << aux << '\n';
            parse(aux);
            init_coada(aux, interior);
            double val = valpostfix(interior);
            //cout << val << '\n';
            if (functions[i] == "sin") {
                val = sin(val * pi / 180);
            }
            else if (functions[i] == "cos") {
                val = cos(val * pi / 180);
            }
            else if (functions[i] == "tg") {
                val = tan(val * pi / 180);
            }
            else if (functions[i] == "round") {
                val = round(val);
            }
            else if (functions[i] == "sqrt") {
                if (val < 0) throw - 2;
                val = sqrt(val);
            }
            else if (functions[i] == "log10") {
                if (val <= 0) throw - 3;
                val = log10(val);
            }
            else if (functions[i] == "log2") {
                if (val <= 0) throw - 3;
                val = log2(val);
            }
            else if (functions[i] == "log") {
                if (val <= 0) throw - 3;
                val = log(val);
            }
            else if (functions[i] == "abs") {
                val = abs(val);
            }
            string val_s = to_string(val);
            x.replace(poz, start - poz + 1, val_s);
            checkNegative(x);
            //cout << x;
        }
    }
}

void parse(string& x) {
    int i;
    spaces(x);
    trigo(x);
    checkNegative(x);
}
