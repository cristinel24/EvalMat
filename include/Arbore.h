#pragma once
arb arb_gen(arb, coada);
arb create_node(string);
void bfs(arb, string []);
bool esteOperator_arb(string);
void init_coada_arb(string, coada&);
void convInfix2Postfix_arb(coada&, coada&);

arb arb_gen(arb tree, coada postfix) {
	string oper[] = { "sin","cos" ,"tg" ,"sqrt" ,"round" ,"ln" ,"log2" ,"lg" ,"abs" };
	stiva_arb st; string x;
	node* temp1 = nullptr, *temp2= nullptr;
	while (!postfix.empty()) {
		x = postfix.front(); postfix.pop();
		tree = create_node(x);
		if (!esteOperator_arb(x))
			st.push(tree);	
		else {
			temp1 = new node; temp2 = new node;
			temp1 = st.top(); st.pop();
			
			bool ok = 1;
			for (int i = 0; i < 9; i++)
				if (x == oper[i]) { ok = 0; break; }
			if (ok) { 
				temp2 = st.top(); st.pop();
				tree->st = temp2; 
			}
			tree->dr = temp1;
			st.push(tree);
		}
	}
	return tree;
}
arb create_node(string info) {
	node* temp = new node;
	temp->val = info;
	temp->st = NULL;
	temp->dr = NULL;	
	return temp;
}
void bfs(arb r, string s[]) {
	if (r == nullptr) return;
	int prim, ultim, i = 0;
	node* c[512], * vf;
	c[0] = r; prim = ultim = 0;
	while (prim <= ultim)
	{
		vf = c[prim++];
		s[i++] = vf->val;
		if (vf->st) c[++ultim] = vf->st;
		if (vf->dr) c[++ultim] = vf->dr;
	}
}
bool esteOperator_arb(string x) { ///returneaza 1 daca se gaseste in lista de operanzi, 0 altfel
	string operatori[] = { "", "+","-","/","*","(",")","%","&","|","^","<",">","=","xor", ">=", "<=", "!=","sin","cos" ,"tg" ,"sqrt" ,"round" ,"ln" ,"log2" ,"lg" ,"abs"};
	for (int i = 1; i < 26; i++)
		if (operatori[i] == x) return 1;
	return 0;
}
void init_coada_arb(string x, coada& infix) {
	string aux;
	for (int i = 0; i < x.size(); i++) {
		if (esteOperator_arb(string(1, x[i])) && (x[i] != '<' && x[i] != '>' && x[i + 1] != '='))
			infix.push(string(1, x[i]));
		else {
			string aux2 = "", variabila = ""; bool isvar = 0; int j;
			for (j = i; isalpha(x[j]) || x[j] == '_' || (x[j]== '2' && j>0 && x[j-1]=='g'); j++) {
				variabila += x[j];
				isvar = 1;
			}
			if (isvar) {
				infix.push(variabila); i = j - 1;
			}
			else {
				while (x[i] && (x[i] < '0' || x[i]>'9') && x[i] != '(') {
					if (x[i + 1]) {
						aux2 = string(1, x[i]) + string(1, x[i + 1]);
						if (esteOperator_arb(aux2)) break;
					}
					aux += x[i++];
					if (esteOperator_arb(aux)) break;
				}
				if (aux != "" && esteOperator_arb(aux) || aux2 != "" && esteOperator_arb(aux2))
				{
					if (aux == "") {
						aux = aux2;
						i += 2;
					}
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
	}
	for (int i = 0; i < infix.size(); i++) {
		if (infix.c[i] == "-" && i == 0 || infix.c[i] == "-" && esteOperator(infix.c[i - 1])) {
			infix.c[i] = to_string(0 - stod(infix.c[i + 1]));
			for (int j = i + 1; j < infix.size(); j++)
				infix.c[j] = infix.c[j + 1];
			infix.c[infix.size()] = "";
		}
	}
}
void convInfix2Postfix_arb(coada& infix, coada& postfix) {
	stiva S; string x;
	init(); /// Initiez prioritatile operanzilor
	while (!infix.empty()) {
		x = infix.front(); infix.pop();
		if (!esteOperator_arb(x)) ///Verific daca nu este operand
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