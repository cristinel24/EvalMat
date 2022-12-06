#pragma once
#include <map>

map<string, int> priot;

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
};

struct node {
	string val;
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

	priot.insert({ "cos", 1 });
	priot.insert({ "sin", 1 });
	priot.insert({ "tg", 1 });
	priot.insert({ "log2", 1 });
	priot.insert({ "ln", 1 });
	priot.insert({ "sqrt", 1 });
	priot.insert({ "round", 1 });
	priot.insert({ "lg", 1 });
	priot.insert({ "abs", 1 });

	priot.insert({ "*", 2 });
	priot.insert({ "-", 2 });
	priot.insert({ "<", 2 });
	priot.insert({ ">", 2 });

	priot.insert({ "%", 3 });
	priot.insert({ "*", 3 });
	priot.insert({ "/", 3 });

	priot.insert({ "(", 4 });
	priot.insert({ ")", 4 });

}
coada infix;

