#pragma once
#include <string>
#include <cmath>
char operanzi[] = "+-/*()%&|^<>=";

bool operand(string x) { ///returneaza 1 daca se gaseste in lista de operanzi, 0 altfel
	return strchr(operanzi,x[0]);
}

void convInfix2Postfix(coada& infix, coada& postfix) {
	stiva S; string x;
	init(); /// Initiez prioritatile operanzilor
	while (!infix.empty()) {
		x = infix.front(); infix.pop();
		if (!operand(x)) ///Verific daca nu este operand
			postfix.push(x);
		else {
			if (x == ")") {
				while (S.top() != "(") {
					postfix.push(S.top()); S.pop();
				}
				S.pop();
			}
			else {
				while (!S.empty() && S.top() != "(" && priot[S.top()] >= priot[x]) {
					postfix.push(S.top()); S.pop();
				}
				S.push(x);
			}
		}
	}
	while (!S.empty()) {
		postfix.push(S.top());
		S.pop();
	}
}

double valpostfix(coada& infix) {
	coada postfix;
	convInfix2Postfix(infix, postfix); //generez notarea postfixata in coada "postifx"
	stiva S; //Stiva S
	string x, st, dr;
	double val, valst, valdr;
	while (!postfix.empty()) {
		x = postfix.front(); postfix.pop();
		if (!operand(x)) ///Verific daca nu este operand
			S.push(x);
		else {
			dr = S.top(); S.pop();
			st = S.top(); S.pop();
			valdr = stod(dr); //transforma din string in double
			valst = stod(st);
			switch (x[0]) {
				case '+': val = valst + valdr; break;
				case '-': val = valst - valdr; break;
				case '*': val = valst * valdr; break;
				case '/': 
					if (valdr == 0) throw -1;
					val = valst / valdr; break;
				case '%': val = int(valst) % int(valdr); break;
				case '|': val = (valst || valdr); break;
				case '&': val = (valst && valdr); break;
				case '^': 
					if ((valst && !valdr) || (!valst && valdr)) val = 1;
					else val = 0;
					break;
				case '<': val = (valst < valdr); break;
				case '>': val = (valst > valdr); break;
				case '=': val = (valst == valdr); break;
			}
			string val_s = to_string(val); //transform din double in string
			S.push(val_s); //pun string in stiva
		}
	}
	x = S.top(); S.pop();
	val = stod(x);
	return val;
}
