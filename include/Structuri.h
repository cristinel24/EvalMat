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
void init() {
	priot.insert({ "=", 1 });
	priot.insert({ "|", 1 });
	priot.insert({ "&", 1 });

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
arb prim;