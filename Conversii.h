#pragma once
#include <string>
char operanzi[] = "+-/*()%";

bool operand(string x) {
	return strchr(operanzi,x[0]);
}

void convInfix2Postfix(queue<string>& infix) {
	stack<string> S;
	init();
	string x;
	while (!infix.empty()) {
		x = infix.front(); infix.pop();
		if (!operand(x))
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

double valpostfix(queue<string>& postfix) {
	convInfix2Postfix(infix);
	stack<string> S;
	string x, st, dr;
	double val, valst,valdr;
	while (!postfix.empty()) {
		x = postfix.front(); postfix.pop();
		if (!operand(x))
			S.push(x);
		else {
			dr = S.top(); S.pop();
			st = S.top(); S.pop();
			valdr = stod(dr);
			valst = stod(st);
			switch (x[0]) {
				case '+': val = valst + valdr; break;
				case '-': val = valst - valdr; break;
				case '*': val = valst * valdr; break;
				case '/': 
					if (valdr == 0) throw new exception("Impartire la zero!");
					val = valst / valdr; break;
				case '%': val = int(valst) % int(valdr); break;
			}
			string val_s = to_string(val);
			S.push(val_s);
		}
	}
	x = S.top(); S.pop();
	val = stod(x);
	return val;
}
