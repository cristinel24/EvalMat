#pragma once
bool check_variable(char*);
void delete_var(char*);
void delete_variables();



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
		if (i == 0 && !isalpha(variabila[0])) throw invalid_argument("Invalid variable name!");
		else if (!(isalnum(variabila[i]) || variabila[i] == '_')) {
			string err = "Invalid variable name! Character: '" + string(1, variabila[i]) + "' forbidden!";
			throw invalid_argument(err);
		}
	}
	coada infix; string val_s = valoare, var_s = variabila;
	
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