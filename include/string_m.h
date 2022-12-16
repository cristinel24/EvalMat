#pragma once

const double pi = 3.14159265;

void init_coada(string, coada&);
void spaces(string&);
void checkNegative(string&);
void trigo(string&);
void parse(string&);
void variables(string&);

void init_coada(string x, coada& infix) {
    string aux;
    for (int i = 0; i < x.size(); i++) {
        if(esteOperator(string(1,x[i])) && (x[i]!='<' && x[i]!='>' && x[i+1]!='='))
            infix.push(string(1, x[i]));
        else {
            string aux2 = "";
            while (x[i] && (x[i] < '0' || x[i]>'9') && x[i] != '(') {
                if (x[i + 1]) {
                    aux2 = string(1, x[i]) + string(1, x[i + 1]);
                    if (esteOperator(aux2)) break;
                }
                aux += x[i++];
                if (esteOperator(aux)) break;
            }
            if (aux != "" && esteOperator(aux) || aux2!="" && esteOperator(aux2))
            {
                if (aux == "") {
                    aux = aux2;
                    i += 2;
                }
                infix.push(aux);
                aux = ""; i--;
            }
            else if (aux != "") {
                if (esteOperator(string(1, aux[aux.size()-1]))) aux = aux.substr(0, aux.size() - 1);
                string invalid = "'" + aux + "'";
                invalid += " was not defined!";
                throw invalid_argument(invalid);
            }
            else {
                int start = i, lg = 0;
                while (x[i] >= '0' && x[i] <= '9' || x[i] == '.') { i++, lg++; }
                string nr = x.substr(start, lg); i--;
                infix.push(nr);
            }
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
        else if (x[i] == '-' && esteOperator(string(1, x[i - 1])) && x[i - 1]!=')') {
            aux = x.substr(0, i);
            aux += "0";
            aux += x.substr(i, x.size() - i);
        }
        if (aux != "") x = aux;
    }
    //cout << x << '\n';
}
void trigo(string& x) {
    string functions[] = { "sin","cos","tg","round","sqrt","lg" ,"log2" ,"ln" , "abs"};
    int size = 10; string aux;
    coada interior;
    checkNegative(x);
    for (int i = 0; i < size; i++) {
        int poz = x.find(functions[i]);
        while(poz != string::npos) {
            if (poz > -1) {
                aux = "";
                int start = poz + functions[i].size() + 1, paranteze = 1;
                while (paranteze) {
                    if (start > x.size()) break;
                    if (x[start] == '(') paranteze++;
                    else if (x[start] == ')') paranteze--;
                    if (paranteze) aux += x[start++];
                }
                if (paranteze) throw invalid_argument("Incorect parenthesis!");
                if (aux == "") throw invalid_argument("Invalid argument of '" + functions[i] + "'");
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
                    if (val < 0) throw invalid_argument("Square root of negative number!");
                    val = sqrt(val);
                }
                else if (functions[i] == "lg") {
                    if (val <= 0) throw invalid_argument("Logarithm of negative number or zero!");
                    val = log10(val);
                }
                else if (functions[i] == "log2") {
                    if (val <= 0) throw invalid_argument("Logarithm of negative number or zero!");
                    val = log2(val);
                }
                else if (functions[i] == "ln") {
                    if (val <= 0) throw invalid_argument("Logarithm of negative number or zero!");
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
            poz = x.find(functions[i], poz + 1);
        }
    }
}

void parse(string& x) {
    int paranteze = 0, i;
    for (i = 0; i < x.size(); i++)
        if (x[i] == '(') paranteze++;
        else if (x[i] == ')') paranteze--;
    if(paranteze) throw invalid_argument("Incorect parenthesis!");
    for (i = 0; i < x.size()-1; i++)
        if(x[i]!='(' && esteOperator(string(1, x[i])) && x[i + 1] == '-')
            throw invalid_argument("Negative number must be between brackets!");
    spaces(x);
    trigo(x);
    checkNegative(x);
}
void variables(string& x) {
    map<string, double>::reverse_iterator i;
    int state;
    for (i = variabile_map.rbegin(); i != variabile_map.rend(); i++) { ///Ma plimb prin map de la coada la cap
        state = x.find(i->first); 
        while (state != string::npos) {
            if (state != -1) {
                if(state == 0 && x.size() == i->first.size() || state == 0 && esteOperator(string(1, x[state + (i->first).size()])) || (state + (i->first).size() == x.size()) || state > 0 && esteOperator(string(1, x[state - 1])) && esteOperator(string(1, x[state + (i->first).size() ])))
                x.replace(state, (i->first).size(), "(" + to_string(i->second) + ")");
            }
            state = x.find(i->first, state + 1);
        }
    }
    int pifind = x.find("pi");
    while (pifind != string::npos) {
        if (pifind == 0 && x.size() == 2 || pifind == 0 && esteOperator(string(1, x[pifind + 2])) || (pifind + 2 == x.size()) || pifind > 0 && esteOperator(string(1, x[pifind - 1])) && esteOperator(string(1, x[pifind + 2])))
            x.replace(x.find("pi"), 2, "(" + to_string(3.14159265359) + ")");
        pifind = x.find("pi", pifind + 1);
    }
    int efind = x.find("e");
    while (efind != string::npos) {
        if (efind == 0 && x.size() == 1 || efind == 0 && esteOperator(string(1, x[pifind + 1])) || (efind + 1 == x.size()) || efind > 0 && esteOperator(string(1, x[efind - 1])) && esteOperator(string(1, x[efind + 1])))
            x.replace(x.find("e"), 1, "(" + to_string(2.71828182846) + ")");
        efind = x.find("e", efind + 1);
    }
   
}