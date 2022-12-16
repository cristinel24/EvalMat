#pragma once
#include <map>
#include "utilis.h"

map<string, int> priot;
map<string, double> variabile_map;

struct stiva {
	int vf = 0;
	string s[NMAX];
	bool empty() {
		return s[vf].empty();
	}
	void pop() {
		s[vf--].clear();
	}
	void push(string x) {
		s[++vf] = x;
	}
	string top() {
		return s[vf];
	}
};
struct coada {
	int prim=0, ultim=-1;
	string c[NMAX];
	bool empty() {
		return c[prim].empty();
	}
	string front() {
		return c[prim];
	}
	void pop() {
		c[prim++].clear();
	}
	void push(string x) {
		c[++ultim] = x;
	}
	int size() {
		return ultim + 1;
	}
};

struct node {
	string val;
	int niv, col;
	node* st, * dr;
};
typedef node* arb;
struct stiva_arb {
	int vf = -1;
	node* s[NMAX] = { nullptr };
	bool empty() {
		if (vf > 0)
			return s[vf - 1];
		else return s[vf];
	}
	void pop() {
		s[vf--]=nullptr;
		if (vf < 0) vf = 0;
	}
	void push(node* x) {
		node* aux = new node;
		aux->val = x->val;
		aux->st = x->st;
		aux->dr = x->dr;
		s[++vf] = aux;
	}
	node* top() {
		if (vf == -1) return nullptr;
		return s[vf];
	}
};

void init() {
	priot.insert({ "=", 1 });
	priot.insert({ "|", 1 });
	priot.insert({ "&", 1 });
	priot.insert({ "xor", 1 });
	priot.insert({ "<", 1 });
	priot.insert({ "<=", 1 });
	priot.insert({ ">", 1 });
	priot.insert({ ">=", 1 });
	priot.insert({ "!=", 1 });

	

	priot.insert({ "+", 2 });
	priot.insert({ "-", 2 });

	priot.insert({ "%", 3 });
	priot.insert({ "*", 3 });
	priot.insert({ "/", 3 });

	priot.insert({ "^", 4 });

	priot.insert({ "cos", 5 });
	priot.insert({ "sin", 5 });
	priot.insert({ "tg", 5 });
	priot.insert({ "log2", 5 });
	priot.insert({ "ln", 5 });
	priot.insert({ "sqrt", 5 });
	priot.insert({ "round", 5 });
	priot.insert({ "lg", 5 });
	priot.insert({ "abs", 5 });

	priot.insert({ "(", 100 });
	priot.insert({ ")", 100 });
}
coada infix;
Console console;


