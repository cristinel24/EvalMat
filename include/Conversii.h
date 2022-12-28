#pragma once
#include <string>
#include <cmath>

bool esteOperator(string);
void convInfix2Postfix(coada&, coada&);
double valpostfix(coada&);

bool esteOperator(string x) {
	string operatori[] = { "", "+","-","/","*","(",")","%","&","|","^", ">=", "<=","<",">","=","xor","!="};
	for (int i = 1; i < 18; i++)
		if (operatori[i] == x) return 1;
	return 0;
}
void convInfix2Postfix(coada& infix, coada& postfix) {
	stiva S; string x;
	init(); /// Initiez prioritatile operanzilor
	while (!infix.empty()) {
		x = infix.front(); infix.pop();
		if (!esteOperator(x)) ///Verific daca nu este operand
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
		if (!esteOperator(x)) ///Verific daca nu este operand
			S.push(x);
		else {
			dr = S.top(); S.pop();
			st = S.top(); S.pop();
			try {
				valdr = stod(dr); //transforma din string in double
				valst = stod(st);
			}
			catch (exception& e){
				throw invalid_argument("Invalid expression!");
			}

			if (x == "+") {
				val = valst + valdr;
			}
			else if (x == "-") {
				val = valst - valdr;
			}
			else if (x == "*") {
				val = valst * valdr;
			}
			else if (x == "/") {
				if (valdr == 0) throw invalid_argument("Divided by zero!");
				val = valst / valdr;
			}
			else if (x == "%") {
				if(int(valst) != valst || int(valdr) != valdr) throw invalid_argument("Can't use '%' on non-int numbers!");
				if (valdr == 0) throw invalid_argument("Divided by zero!");
				val = int(valst) % int(valdr);
			}
			else if (x == "|") {
				val = (valst || valdr);
			}
			else if (x == "&") {
				val = (valst && valdr);
			}
			else if (x == "^") {
				val = pow(valst, valdr);
			}
			else if (x == "<") {
				val = (valst < valdr);
			}
			else if (x == ">") {
				val = (valst > valdr);
			}
			else if (x == "=") {
				val = (valst == valdr);
			}
			else if (x == ">=") {
				val = (valst >= valdr);
			}
			else if (x == "<=") {
				val = (valst <= valdr);
			}
			else if (x == "xor") {
				if ((valst && !valdr) || (!valst && valdr)) val = 1;
				else val = 0;
			}
			else if (x == "!=") {
				val = (valst != valdr);
			}
			else {
				throw invalid_argument("Invalid operator!");
			}
			string val_s = to_string(val); //transform din double in string
			S.push(val_s); //pun string in stiva
		}
	}
	if(!S.empty()) x = S.top(); S.pop();
	if(S.top()!="") throw invalid_argument("Invalid operator!"); //daca a mai ramas cv in stiva sigur nu e corect
	val = stod(x);
	if (val == -0) val = 0;
	return val;
}
