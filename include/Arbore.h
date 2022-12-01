#pragma once

void arb_gen(coada postfix);
void gen(arb&, stiva&);
void bfs(arb);

void arb_gen(coada postfix) {
	stiva S;
	while (!postfix.empty()) {
		S.push(postfix.front());
		postfix.pop();
	}
	arb Alexandru_Mitreanu=nullptr;
	gen(Alexandru_Mitreanu, S);
	bfs(Alexandru_Mitreanu);
}
void gen(arb& A, stiva& S) {
	string x = S.top(); S.pop();
	node* p = new node;
	p->val = x;
	if (A == nullptr)
		A = p;	
	if (esteOperator(x)) {
		gen(p->dr, S);
		gen(p->st, S);
	}
}
void bfs(arb r)
{
	if (r == nullptr) return;
	int prim, ultim, i = 0;
	arb c[512], vf;
	c[0] = r; prim = ultim = 0;
	while (prim <= ultim)
	{
		vf = c[prim++];
		cout << vf->val << ' ';
		if (vf->st) c[++ultim] = vf->st;
		if (vf->dr) c[++ultim] = vf->dr;
	}
}