#pragma once
//#define back_color COLOR(40, 41, 43) //culoare backgroundului
//#define primary COLOR(54, 114, 174) //bleu
//#define secondary COLOR(236, 160, 64) //orange
bool check_variable(char*);
void delete_var(char*);
void delete_variables();
void nivels(arb, int);
void columns(arb, int, int, int&);
void draw(string, int, int, int, int);

int get_max_level(arb);
int get_max_column(arb);
int offset = 10;

bool check_variable(char* s) {
	///Copiez in sirul 'variabila' variabila
	char variabila[NMAX], valoare[1024]; strcpy(variabila, s);
	char* pch = strchr(variabila, '='); //caut caracterul '='
	
	if (pch != NULL && *(pch + 1) != NULL) ///Daca am gasit egal
		strcpy(valoare, pch + 1);
	else throw invalid_argument("Missing right value of '='!"); ///Daca nu am gasit nici un egal

	string x = valoare;
	variables(x); ///inlocuieste variabilele cu valorile lor

	strcpy(valoare, x.c_str());
	///dau check sa vad daca exista ")("
	for (int i = 1; i < strlen(valoare); i++)
		if (x[i] = '(' && x[i - 1] == ')') throw invalid_argument("Operator missing!");
	
	if (valoare[strlen(valoare) - 1] == ';') valoare[strlen(valoare) - 1] = 0; ///scot caracterul ';' daca exista

	*pch = 0;
	if (strlen(variabila) < 1) throw invalid_argument("Missing left value of '='!");

	int i = 0;
	///Verific daca variabila este corect sintactic (primul caracter e o litera, urmatoarele sunt alfanumerice sau '_'
	for (i = 0; i < strlen(variabila); i++) {
		if (i == 0 && !isalpha(variabila[0]) && variabila[0] != '_') throw invalid_argument("Invalid variable name!");
		else if (!(isalnum(variabila[i]) || variabila[i] == '_')) {
			string err = "Invalid variable name! Character: '" + string(1, variabila[i]) + "' forbidden!";
			throw invalid_argument(err);
		}
	}
	coada infix; string val_s = valoare, var_s = variabila;

	string reserved_words[] = { "e", "pi", "sin","cos","tg","round","sqrt","lg" ,"log2" ,"ln" , "abs", "cbrt"};

	for (int i = 0; i < 12; i++)
		if (reserved_words[i] == var_s) throw invalid_argument(string("'" + var_s + "' is a reserved word!"));
	
	
	double val = INFINITE;
	try {
		parse(val_s);
		init_coada(val_s, infix);
		val = valpostfix(infix);
	}
	catch (invalid_argument& e) {
		throw invalid_argument(e.what());
		return 0;
	}
	if (val != INFINITE && variabila) {
		if (variabile_map.find(var_s) != variabile_map.end()) { ///daca gasesc ca variabila este deja definita
			string err ="'" + var_s + "' was already defined!";
			throw invalid_argument(err);
			//variabile_map.erase(var_s);
		}
		variabile_map.insert({ var_s, val }); //daca nu, o introduc in map
	}
	return 1;
}
void delete_var(char* s) {
	char variabila[NMAX]; strcpy(variabila, s);
	char* pch = strchr(variabila, '=');
	*pch = 0;
	variabile_map.erase(variabila);
	//cout << "Am sters din map variabila: " << variabila << '\n';
}
void delete_variables() {
	variabile_map.erase(variabile_map.begin(), variabile_map.end());
}
string one[] = { "sin","cos","tg","round","sqrt","lg" ,"log2" ,"ln" , "abs" };
int get_max_level(arb a) {
	if (a == NULL) return 0;
	int n1 = get_max_level(a->st);
	int n2 = get_max_level(a->dr);
	return 1 + max(n1, n2);
}
int get_max_column(arb a) {
	if (a == NULL) return 0;
	int n1 = get_max_column(a->st);
	int n2 = get_max_column(a->dr);
	return 1 + n1 + n2;
}

arb initArb(string xarb) {
	coada infix, postfix;
	arb T = nullptr; string arr[NMAX];
	spaces(xarb);
	init_coada_arb(xarb, infix);
	convInfix2Postfix_arb(infix, postfix);
	return arb_gen(T, postfix);
}

void nivels(arb a, int nivel) {
	if (a != NULL) {
		a->niv = nivel;
		nivels(a->st, nivel + 1);
		nivels(a->dr, nivel + 1);
	}
}
void columns(arb a, int n_size, int c_size, int& contor) {
	setlinestyle(0, SOLID_LINE, 10);
	setcolor(COLOR(236, 160, 64));
	if (a != NULL) {
		columns(a->st, n_size, c_size, contor);
		draw(a->val, a->niv, ++contor, n_size, c_size);
		a->col = contor;
		columns(a->dr, n_size, c_size, contor);
	}
}
void linii(arb a, int n_size, int c_size) {
	setlinestyle(0, SOLID_LINE, 2);
	setcolor(COLOR(236, 160, 64));
	
	if (a != NULL) {
		if (a->st) line(a->col * c_size - c_size / 2, a->niv * n_size - n_size / 2 + offset, a->st->col * c_size - c_size / 2, a->st->niv * n_size - n_size / 2 - offset);
		if (a->dr) line(a->col * c_size - c_size / 2, a->niv * n_size - n_size / 2 + offset, a->dr->col * c_size - c_size / 2, a->dr->niv * n_size - n_size / 2 - offset);

		linii(a->st, n_size, c_size);
		linii(a->dr, n_size, c_size);
	}
}
void draw(string s, int niv, int col, int n_size, int c_size) {
	setfillstyle(SOLID_FILL, COLOR(54, 114, 174));
	int xc = col * c_size - c_size / 2, yc = niv * n_size - n_size / 2;
	setcolor(COLOR(236, 160, 64));
	setbkcolor(COLOR(40, 41, 43)); 
	setlinestyle(0, SOLID_LINE, 2);

	int lg = s.size() * 5;
	outtextxy(xc - 3 * lg / 4, yc - 8, _strdup(s.c_str()));

	setcolor(COLOR(54, 114, 174));
	ellipse(xc, yc, 0, 360, lg + 10, 10);
	

	setcolor(COLOR(236, 160, 64));
}


